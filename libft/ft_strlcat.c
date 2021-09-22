/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:41 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/04 18:18:18 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_lenght;
	size_t	src_lenght;

	dst_lenght = ft_strlen(dst);
	src_lenght = ft_strlen((char *)src);
	if (size <= dst_lenght)
		return (src_lenght + size);
	i = dst_lenght;
	j = 0;
	while (i < size - 1 && src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (src_lenght + dst_lenght);
}
