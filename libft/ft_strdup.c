/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:42:35 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/01/27 13:35:17 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	lenght;
	char	*str;

	lenght = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (str)
		ft_strlcpy(str, s, lenght + 1);
	return (str);
}
