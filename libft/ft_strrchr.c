/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:52:11 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/01/26 18:06:20 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				j;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			j = i;
		i++;
	}
	if (c == '\0')
		j = i;
	if (j == 0 && str[j] != c)
		return (0);
	return ((char *)&str[j]);
}
