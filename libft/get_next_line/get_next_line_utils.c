/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:01:33 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/02/09 20:02:00 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	ft_list_clear(t_datalst *dt)
{
	t_listc	*rest;
	t_listc	*elem;

	elem = dt->firts;
	while (elem)
	{
		rest = elem->next;
		free(elem->str);
		free(elem);
		elem = rest;
	}
	dt->firts = 0;
	dt->last = 0;
	dt->len = 0;
}
