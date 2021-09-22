/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:18:02 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/02/11 12:01:48 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_delete_front(t_datalst *dt)
{
	t_listc	*delete;

	if (dt && dt->firts)
	{
		if (dt->firts == dt->last)
		{
			free(dt->firts->str);
			dt->firts->str = 0;
			free(dt->firts);
			dt->firts = 0;
			dt->last = 0;
		}
		else
		{
			delete = dt->firts;
			dt->firts = dt->firts->next;
			free(delete->str);
			delete->str = 0;
			free(delete);
		}
		dt->len--;
	}
}

t_listc	*ft_new_elem(t_datalst *dt)
{
	t_listc	*new;

	new = (t_listc *)malloc(sizeof(t_listc));
	if (!new)
		return (0);
	new->str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new->str)
	{
		free(new);
		return (0);
	}
	new->next = 0;
	new->str[BUFFER_SIZE] = '\0';
	if (!dt->firts)
		dt->firts = new;
	if (dt->last)
		dt->last->next = new;
	dt->last = new;
	dt->len++;
	return (new);
}

void	ft_list_clear(t_fds *fds, int fd)
{
	t_listc		*rest;
	t_listc		*elem;
	t_datalst	**actual;

	if (fds->select && fd >= 0)
	{
		elem = fds->select->firts;
		while (elem)
		{
			rest = elem->next;
			free(elem->str);
			free(elem);
			elem = rest;
		}
		actual = &fds->fds;
		while ((*actual) && (*actual)->fd != fd)
			actual = &(*actual)->next;
		*actual = fds->select->next;
		free(fds->select);
		fds->select = 0;
	}
}
