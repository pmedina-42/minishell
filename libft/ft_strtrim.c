/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:00:22 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/04 20:01:00 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	int				end;
	char			*str;
	unsigned char	*us1;

	if (s1 && set)
	{
		us1 = (unsigned char *)s1;
		i = 0;
		while (us1[i] && ft_strchr(set, us1[i]))
			i++;
		end = ft_strlen(s1);
		while (us1[i] && ft_strchr(set, us1[end - 1]))
			end--;
		if (!us1[i])
			str = ft_strdup("");
		else
			str = ft_substr(s1, i, end - i);
		return (str);
	}
	return (0);
}
