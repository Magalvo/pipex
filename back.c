/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:33:44 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/23 11:42:42 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

/* void	pipe_parsing(char **argv, char **envp)
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
	while (*paths)
	{
		len = ft_strlen(*paths)-1;
		if (**paths+len != '/')
			*paths = ft_strjoin(*paths, "/");
		paths++;
	}
	args = ft_split(argv[2], ' ');
} */

char	*pipe_parsing(t_pipex *pipx, char **argv, char **envp)
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
	/*
	i = -1;
	char *cmd;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], args[0]);
		if (execve(cmd, args, envp) == -1)
			perror("execve fail: \n");
		free(cmd);
	}
	exit(EXIT_FAILURE); */


int	main(int argc, char **argv, char **envp)
{
	static t_pipex pipx;
	
	if (argc < 5)
		return (0);
	pipe_parsing(&pipx, argv, envp);

	
	return (0);
}