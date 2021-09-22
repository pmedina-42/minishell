/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:31:47 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/07 16:04:47 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	is_in_range(char *str)
{
	int		len;
	int		nbr;
	char	*copy;

	len = ft_strlen(str);
	if ((str[0] != '-' && len > 10) || len > 11)
		return (0);
	else if (len >= 10)
	{
		copy = ft_strdup(str);
		copy[len - 1] = '\0';
		nbr = ft_atoi(copy);
		free(copy);
		if (nbr > 214748364 || nbr < -214748364)
			return (0);
		if (nbr == 214748364 || nbr == -214748364)
		{
			if (str[len - 1] - '0' > 8)
				return (0);
			if (str[len - 1] - '0' == 8 && str[0] != '-')
				return (0);
		}
	}
	return (1);
}

int	ft_str_is_nbr(char *str)
{
	char	*temp;

	temp = str;
	if (*str != '-' && *str != '+' && !ft_isdigit(*str))
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	if (!is_in_range(temp))
		return (0);
	return (1);
}
