/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:33:44 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/03 18:05:00 by dde-maga         ###   ########.fr       */
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
	while (*paths)
	{
		len = ft_strlen(*paths)-1;
		if (**paths+len != '/')
			*paths = ft_strjoin(*paths, "/");
		paths++;
	}
	args = ft_split(argv[2], ' ');
}