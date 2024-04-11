/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:36:14 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/11 18:00:09 by dde-maga         ###   ########.fr       */
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


void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		fd[2];
	pid_t	child1;
	pid_t	child2;
	
	pipe_parsing(argv, envp);
	
	pipe(fd);
	child1 = fork();
	if (child1 < 0 || !fd1 || !fd2)
		return (perror("Fork: "));
	if (child1 == 0)
	{
		close(fd[0]);
		
	}
	
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	*pids;
	int		fd1;
	int		fd2;
	int		*fds[2];
	int		i;
	
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc-1], O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	
	pipe(fds);
	if (fd1 == -1 || fd2 == -1)
		return (perror("Error:"), -1);
	
	pids = malloc(sizeof(int) * argc - 5);
	if (!pids)
		perror("Allocation Error: ");
	while (i < argc - 5)
	{
		pids[i]= fork();
	}
	


	
	//pipex(fd1, fd2, argv, envp);
	
	return (0);
}
