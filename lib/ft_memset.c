/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:34:03 by dde-maga          #+#    #+#             */
/*   Updated: 2024/02/14 18:08:31 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pos;
	unsigned char	ac;

	ac = (unsigned char)c;
	pos = (unsigned char *)b;
	while (len--)
		*pos++ = ac;
	return (b);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*altdest;
	unsigned char	*altsrc;

	altdest = (unsigned char *)dest;
	altsrc = (unsigned char *)src;
	if (!altdest && !altsrc)
		return (NULL);
	while (n-- > 0)
	{
		*altdest = *altsrc;
		altdest++;
		altsrc++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	if (new_size <= old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
