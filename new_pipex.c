/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:36:14 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/24 14:41:27 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"


char	*env_paths(t_pipex *pipx, char **argv, char **envp)
{
	char	**paths;
	char	**args;
	int		i;
	int		len;
	
	len = 0;
	i = 0;
	args = ft_split(argv[2], ' ');
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++; 
	printf("Path len: %s\n", *envp);
	paths = ft_split(*envp+5, ':');
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
			paths[i] = ft_strjoin(paths[i], "/");
		printf ("Paths[%i]: %s\n", i, paths[i]);
		i++;
	}
	pipx->cmd_paths = paths;
	return (NULL);
}

char	*args_parsing(char **argv, char **envp)
{
	char	**paths;
	char	**args;
	int		i;
	
	args = ft_split(argv[2], ' ');
	
	i = -1;
	char *cmd;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], args[0]);
		if (execve(cmd, args, envp) == -1)
			perror("execve fail: \n");
		free(cmd);
	}
	exit(EXIT_FAILURE);
}


int	arg_check(char **argv, t_pipex *pipex)
{
	if (argv && !ft_strncmp("here_doc", argv[1], 9))
		return (pipex->here_doc = 1, 6);
	else 
		return (pipex->here_doc = 0, 5);
}

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	ft_infile(t_pipex *pipex, char **argv)
{
	if (pipex->here_doc)
		here_doc(argv[2], pipex);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			error_msg("infile err");
	}
	return (1);
}
int	ft_outfile(t_pipex *pipex, char *argv)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv, O_WRONLY | O_RDONLY | O_APPEND, S_IRWXU);
	else
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (pipex->here_doc < 0)
		error_msg("outfile err");
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex;
	
	if (argc < arg_check(argv[1], &pipex))
		ft_putchar_fd("Number or args", 2);
	
	ft_infile(&pipex, argv);
	ft_outfile(&pipex, argv[argc-1]);	
	pipex.cmd_nbr = argc - 3 - pipex.here_doc;
	pipex.pipe_nbr = 2 * (pipex.cmd_nbr - 1);
	pipex.pipes = (int *)malloc(sizeof(int) * pipex.pipe_nbr);
	if (!pipex.pipes)
		exit_error("err creating pipes");
	env_paths(&pipex, argv, envp);
	if(!pipex.cmd_paths)
		free_pipes(&pipex);
	
	


	
	//pipex(fd1, fd2, argv, envp);
	
	return (0);
}
