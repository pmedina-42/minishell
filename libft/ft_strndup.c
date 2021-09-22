/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:15:38 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/07/13 19:15:43 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	lenght;
	char	*str;

	lenght = ft_strlen(s);
	if (n < lenght)
		lenght = n;
	str = (char *)malloc(sizeof(char) * (lenght + 1));
	if (str)
		ft_strlcpy(str, s, lenght + 1);
	return (str);
}
