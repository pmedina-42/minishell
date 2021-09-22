/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:01:16 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/02/10 18:15:15 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_has_return(t_datalst *dt)
{
	int		i;
	char	*str;

	if (dt->last)
	{
		str = dt->last->str;
		i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

char	*ft_get_and_delete_line(t_datalst *dt)
{
	int		i;
	int		r;
	char	*str;

	r = ft_has_return(dt);
	str = (char *)malloc(sizeof(char) * ((dt->len * BUFFER_SIZE) + 1));
	if (str)
	{
		i = 0;
		while (dt->firts)
		{
			if (dt->len > 1 || r == -1)
			{
				i += ft_strncpy(&str[i], dt->firts->str, BUFFER_SIZE);
				ft_delete_front(dt);
			}
			else
			{
				ft_strncpy(&str[i], dt->firts->str, r);
				ft_strncpy(dt->firts->str, &dt->firts->str[r + 1], BUFFER_SIZE);
				return (str);
			}
		}
	}
	return (str);
}

int	ft_read_fd(int fd, t_datalst *dt)
{
	t_listc	*elem;
	int		end;
	int		readed;

	end = 0;
	while (ft_has_return(dt) < 0 && !end)
	{
		elem = ft_new_elem(dt);
		if (!elem)
			return (-1);
		readed = read(fd, elem->str, BUFFER_SIZE);
		if (readed == -1)
			return (-1);
		elem->str[readed] = '\0';
		if (readed < BUFFER_SIZE)
			if (!readed)
				end = 1;
	}
	return (end);
}

int	get_next_line(int fd, char **line)
{
	static t_datalst	data = {0, 0, 0};
	int					end;
	int					error;
	char				*str;

	end = 0;
	error = (fd < 0 || !line || BUFFER_SIZE <= 0);
	if (!error && ft_has_return(&data) == -1)
		end = ft_read_fd(fd, &data);
	if (end > 0 && ft_has_return(&data) != -1)
		end = 0;
	str = ft_get_and_delete_line(&data);
	if (error || end == -1 || !str)
	{
		ft_list_clear(&data);
		return (-1);
	}
	*line = ft_strdup(str);
	free(str);
	if (end)
		ft_list_clear(&data);
	return (!end);
}
