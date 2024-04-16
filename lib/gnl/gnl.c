/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:49:14 by dde-maga          #+#    #+#             */
/*   Updated: 2024/03/21 12:47:18 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	if (read(fd, buffer, 0) < 0 || FOPEN_MAX <= fd || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < FOPEN_MAX)
		{
			while (buffer[fd][i])
			{
				buffer[fd][i++] = '\0';
			}
		}
		return (NULL);
	}
	line = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoingnl(line, buffer[fd]);
		ft_clean_buf(buffer[fd]);
		if (line && line[ft_strlengnl(line) - 1] == '\n')
			return (line);
	}
	return (line);
}
