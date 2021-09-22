/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:27:09 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/09/20 20:27:12 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substrdel(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*str1;
	char	*str2;

	if (!s)
		return (0);
	str1 = ft_strndup(s, start);
	if (start + len >= ft_strlen(s))
		str2 = ft_strdup("");
	else
	{
		str2 = ft_strdup(&s[start + len + 1]);
	}
	str = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (str);
}
