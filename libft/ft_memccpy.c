/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:43:06 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/01/26 12:19:57 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*src_str;
	unsigned char	*dst_str;

	if (n == 0)
		return (0);
	src_str = (unsigned char *)src;
	dst_str = (unsigned char *)dst;
	uc = (unsigned char)c;
	i = 0;
	while (src_str[i] != uc && i < n - 1)
	{
		dst_str[i] = src_str[i];
		i++;
	}
	dst_str[i] = src_str[i];
	if (src_str[i] != uc)
		return (0);
	return (&dst_str[i + 1]);
}
