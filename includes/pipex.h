/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:22:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/11 18:04:43 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/libft.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

#ifndef FOPEN_MAX
#define FOPEN_MAX 1024
#endif


typedef struct	s_pipe	t_pipe;
typedef struct	s_cmds	t_cmds;

struct				s_cmds
{
	char			*path;
	char			*args;
	struct s_cmds	*prev;
	struct s_cmds	*next;
};		

struct				s_pipe
{	
	char			**args;
	t_cmds			*command;
	struct s_pipe	*prev;
	struct s_pipe	*next;
};

char	*pipe_parsing(char **argv, char **envp);

#endif
