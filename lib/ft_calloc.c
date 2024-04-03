/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:32:38 by dde-maga          #+#    #+#             */
/*   Updated: 2024/02/14 17:46:53 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;

	out = malloc(nmemb * size);
	if (out == NULL)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (out);
	ft_memset(out, 0, nmemb * size);
	return (out);
}
