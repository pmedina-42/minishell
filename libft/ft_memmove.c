/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:44:20 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/02/01 15:42:06 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*src_str;
	unsigned char	*dst_str;

	src_str = (unsigned char *)src;
	dst_str = (unsigned char *)dst;
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			dst_str[len] = src_str[len];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
