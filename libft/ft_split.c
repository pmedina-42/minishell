/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:10:44 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/17 15:55:42 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_subchr(char const *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str)
		ft_strlcpy(str, s, i + 1);
	return (str);
}

static size_t	ft_count_fragments(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s && s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			i++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**split;

	i = 0;
	count = ft_count_fragments(s, c);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (split)
	{
		split[count] = 0;
		i = 0;
		while (i < count)
		{
			while (*s == c)
				s++;
			split[i++] = ft_subchr(s, c);
			s = ft_strchr(s, c);
			s++;
		}
	}
	return (split);
}
