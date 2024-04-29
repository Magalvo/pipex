/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:26:23 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/24 14:39:32 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"


void	here_doc(char *argv, t_pipex *pipx)
{
	int		file;
	char	*line;
	
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (line < 0)
		exit_error("here doc error");
	while (1)
	{
		ft_putstr_fd("here_doc>", 1);
		if(get_next_line(0) < 0)
			exit(1);
		if(!ft_strncmp(argv, line, ft_strlen(argv) + 1))
			break ;
		write(file, line ,ft_strlen(argv) + 1);
		write(file, "\n", 1);
		free(line);
	}
	free(line);
	close (file);
	pipx->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipx->infile < 0)
	{
		unlink(".here_doc_tmp");
		exit_error("here doc err 2");
	}
}
