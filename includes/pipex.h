/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:22:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/16 15:23:30 by dde-maga         ###   ########.fr       */
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

# define	MAX_ARGS 10
# define	MAX_CMDS 10

typedef struct	s_pipex	t_pipex;
typedef	struct	s_cmds	t_cmds;

struct				s_pipex
{	
	char			**cmd_paths;
	char			*cmd;
	char			**cmd_args;
	int				infile;
	int				outfile;
	int				here_doc;
};

char	*pipe_parsing(char **argv, char **envp);

#endif
