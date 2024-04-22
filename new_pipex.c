/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:36:14 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/22 17:25:23 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"


char	*pipe_parsing(char **argv, char **envp)
{
	char	**paths;
	char	**args;
	int		i;
	int		len;
	
	len = 0;
	i = 0;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++; 
	paths = ft_split(*envp+5, ':');
	printf("Path len: %li\n", ft_strlen(paths[i]));
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] != '/')
			paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
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
		here_doc(argv[1], pipex);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			error_msg("infile err");
	}
		
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
		paths= 
	ft_infile(&pipex, argv);
	ft_outfile(&pipex, argv[argc-1]);	

	while (i < argc - 5)
	{
		pids[i]= fork();
	}
	


	
	//pipex(fd1, fd2, argv, envp);
	
	return (0);
}
