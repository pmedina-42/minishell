/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:57:33 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/04 18:36:07 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_out_range(long nbr, long sign, char c)
{
	int	result;

	result = 1;
	if (nbr > 922337203685477580)
		result = -1;
	else if (sign < 0)
	{
		if (nbr == 922337203685477580 && (c - '0' > 8))
			result = 0;
	}
	else if (nbr == 922337203685477580 && (c - '0' > 7))
		result = -1;
	if (result < 0 && sign < 0)
		result = 0;
	return (result);
}

int	ft_atoi(const char *nptr)
{
	long	nbr;
	long	sign;
	int		i;
	int		out;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			sign *= -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		out = ft_out_range(nbr, sign, nptr[i]);
		if (out <= 0)
			return (out);
		nbr *= 10;
		nbr += nptr[i++] - '0';
	}
	return ((int)(nbr * sign));
}
