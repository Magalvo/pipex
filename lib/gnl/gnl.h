/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:49:58 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/16 16:19:35 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# ifndef FOPEN_MAX
#  define FOPEN_MAX 1024
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlengnl(char *str);
char	*get_next_line(int fd);
char	*ft_strjoingnl(char *s1, char *s2);
void	ft_clean_buf(char *buffer);

#endif
