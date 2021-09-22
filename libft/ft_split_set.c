/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:55:03 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/17 15:58:47 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_subchr(char const *s, char *set)
{
	int		i;
	char	*str;

	i = 0;
	while (!ft_strrchr(set, s[i]) && s[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str)
		ft_strlcpy(str, s, i + 1);
	return (str);
}

static size_t	ft_count_fragments(char const *s, char *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] && ft_strrchr(set, s[i]))
			i++;
		if (s[i] && !ft_strrchr(set, s[i]))
		{
			count++;
			i++;
			while (!ft_strrchr(set, s[i]) && s[i])
				i++;
		}
	}
	return (count);
}

char	**ft_split_set(char const *s, char *set)
{
	size_t	i;
	size_t	count;
	char	**split;

	i = 0;
	count = ft_count_fragments(s, set);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (split)
	{
		split[count] = 0;
		i = 0;
		while (i < count)
		{
			while (ft_strrchr(set, *s))
				s++;
			split[i++] = ft_subchr(s, set);
			while (!ft_strrchr(set, *s))
				s++;
		}
	}
	return (split);
}
