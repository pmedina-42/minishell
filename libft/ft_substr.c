/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:42:59 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/04 17:12:16 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	real_len;
	char	*str;

	if (!s)
		return (0);
	real_len = 0;
	if (start < ft_strlen(s))
		real_len = ft_strlen(&s[start]);
	if (real_len < len)
		len = real_len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str)
		ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
