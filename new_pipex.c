/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:36:14 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/03 18:16:09 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"


void	pipe_parsing(char **argv, char **envp)
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
		cmd = ft_strjoin()
	}
}


void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		fd[2];
	pid_t	child1;
	
	
	pipe_parsing(argv, envp);
	
	pipe(fd);
	child1 = fork();
	if (child1 < 0 || !fd1 || !fd2)
		return (perror("Fork: "));
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int fd2;
	
	if (argc != 5)
		return (0);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	
	if (fd1 == -1 || fd2 == -1)
		return (perror("Error:"), -1);
		
	pipex(fd1, fd2, argv, envp);
	
	return (0);
}