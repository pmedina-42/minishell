/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:12 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/04 19:53:28 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (dst && src)
	{
		while (src[i] != '\0')
		{
			if (i < size && size)
				dst[i] = src[i];
			if (i == size)
				dst[i - 1] = '\0';
			i++;
		}
		if (i == size && size)
			dst[i - 1] = '\0';
		if (i < size)
			dst[i] = '\0';
		return (i);
	}
	return (0);
}
