/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:22:50 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/29 18:47:48 by dde-maga         ###   ########.fr       */
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
#include "../lib/gnl/gnl.h"

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
	pid_t			pid1;
	pid_t			pid2;
	char			**cmd_paths;
	char			*cmd;
	char			**cmd_args;
	int				pipxfd[2];
	int				infile;
	int				outfile;
	int				here_doc;
	int				cmd_nbr;
	int				pipe_nbr;
	int				*pipes;
};

char	*pipe_parsing(t_pipex *pipx, char **argv, char **envp);

void	free_parent(t_pipex *pipx);
void	free_child(t_pipex *pipx);
void	exit_error(char *str);

#endif
