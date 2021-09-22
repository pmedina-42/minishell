/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:32:18 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/04 18:24:12 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;
	t_list	*next;

	if (lst && *lst && del)
	{
		aux = *lst;
		next = aux->next;
		while (aux != 0)
		{
			ft_lstdelone(aux, del);
			aux = next;
			if (!aux)
				next = 0;
			else
				next = aux->next;
		}
		*lst = 0;
	}
}
