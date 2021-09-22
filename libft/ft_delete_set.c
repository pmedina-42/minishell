/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:39:09 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/17 16:08:26 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_delete_set(char **str, char *set)
{
	char	*copy;
	char	*temp;
	int		len;
	int		i;
	int		j;

	temp = *str;
	len = ft_strlen(temp);
	copy = ft_calloc(sizeof(char), len + 1);
	copy[len] = '\0';
	if (copy)
	{
		i = 0;
		j = 0;
		while (i < len && temp[i])
		{
			if (!ft_strrchr(set, temp[i]))
				copy[j++] = temp[i];
			i++;
		}
		free(*str);
		*str = ft_strdup(copy);
		free(copy);
	}
	return (*str);
}
