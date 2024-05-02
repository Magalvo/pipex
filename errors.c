/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:03:13 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/02 19:09:52 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	error_message(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_parent(t_pipex	*pipex)
{
	int	ctd;

	ctd = -1;
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	while (pipex->cmd_paths[++ctd])
		free(pipex->cmd_paths[ctd]);
	free(pipex->cmd_paths);
	free(pipex->pipes);
}

void	free_pipes(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	free(pipex->pipes);
	error_message("Error on Envp");
	exit(1);
}