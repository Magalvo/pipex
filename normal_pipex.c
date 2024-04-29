/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:39:18 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/29 17:03:08 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"


void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_parent(t_pipex *pipx)
{
	int i;

	i = 0;
	close(pipx->infile);
	close(pipx->outfile);
	while(pipx->cmd_paths[i])
		free(pipx->cmd_paths[i++]);
	free(pipx->cmd_paths);
};

void	free_child(t_pipex *pipx)
{
	int i;

	i = 0;
	while (pipx->cmd_args[i])
		free(pipx->cmd_args[i++]);
	free(pipx->cmd_args);
	free(pipx->cmd);
}

void	find_paths(t_pipex *pipx, char **envp)
{
	char	**paths;
	int		i;
	int		len;
	
	len = 0;
	i = 0;
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++; 
	printf("Path len: %s\n", *envp);
	paths = ft_split(*envp+5, ':');
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
			paths[i] = ft_strjoin(paths[i], "/");
		//printf ("Paths[%i]: %s\n", i, paths[i]);
		i++;
	}
	pipx->cmd_paths = paths;
}

static char	*cmd_path(t_pipex *pipx)
{
	char	*cmd;
	char	*firstarg;
	char	**paths;
	
	paths= pipx->cmd_paths;
	firstarg = pipx->cmd_args[0];
	while (*paths)
	{
		cmd = ft_strjoin(*paths, firstarg);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		paths++;
	}
	return (NULL);
}


void	first_command(t_pipex pipx, char **argv, char **envp)
{
	dup2(pipx.pipxfd[1], 1);
	close(pipx.pipxfd[0]);
	dup2(pipx.infile, 0);
	find_paths(&pipx, envp);
	pipx.cmd_args = ft_split(argv[2], ' ');
	pipx.cmd = cmd_path(&pipx);
	if (!pipx.cmd)
	{
		free_child(&pipx);
		exit_error("command");
		exit (EXIT_FAILURE);
	}
	if (execve(pipx.cmd, pipx.cmd_args, envp) == -1)
		exit_error("execution");
}


void	second_command(t_pipex pipx, char **argv, char **envp)
{
	dup2(pipx.pipxfd[0], 0);
	dup2(pipx.infile, 1);
	find_paths(&pipx, envp);
	pipx.cmd_args = ft_split(argv[3], ' ');
	pipx.cmd = cmd_path(&pipx);
	if (!pipx.cmd)
	{
		free_child(&pipx);
		exit_error("command");
		exit (EXIT_FAILURE);
	}
	if (execve(pipx.cmd, pipx.cmd_args, envp) == -1)
		exit_error("execution");
}

int main(int argc, char **argv, char **envp)
{
	t_pipex pipx;
	int in;
	int out;
	int pipesfd[2];
	pid_t pid1;
	pid_t pid2;
	
	
	if (argc < 5)
		exit_error("num of args");
		
	in  = open(argv[1], O_RDONLY);
	if (in < 0)
		exit_error("err opening in file");
	out = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY , 0777);
	if (out < 0)
		exit_error("err opening out file");
	
	pipe(pipesfd);
	
	pid1 = fork();
	if(pid1 == 0)
	{
		find_paths(&pipx, envp);
		pipx.cmd_args = ft_split(argv[2], ' ');
		pipx.cmd = cmd_path(&pipx);
		close(pipesfd[0]);
		dup2(in,0);
		dup2(pipesfd[1],1);
		execve(pipx.cmd,pipx.cmd_args,envp);
		exit(0);
	}
	close(pipesfd[1]);
	close(in);
	
	pid2 = fork();
	if(pid2 == 0)
	{
		find_paths(&pipx, envp);
		pipx.cmd_args = ft_split(argv[3], ' ');
		pipx.cmd = cmd_path(&pipx);
		dup2(pipesfd[0],0);
		dup2(out,1);
		execve(pipx.cmd,pipx.cmd_args,envp);
		exit(0);
	}
	close(pipesfd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	// pipe(pipx.pipxfd);

	// pipx.pid1 = fork();
	// if (pipx.pid1 == 0)
	// 	first_command(pipx, argv, envp);
	// pipx.pid2 = fork();
	
	// close(pipx.infile);
	// close(pipx.pipxfd[1]);
	// if(pipx.pid2 == 0)
	// 	second_command(pipx, argv, envp);
	// close(pipx.pipxfd[0]);

}