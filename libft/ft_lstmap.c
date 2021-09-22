/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:56:37 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/03/04 18:21:50 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*copy;
	t_list	*elem;

	copy = 0;
	while (lst != 0)
	{
		elem = ft_lstnew(f(lst->content));
		if (elem == 0)
		{
			ft_lstclear(&copy, del);
			return (0);
		}
		ft_lstadd_back(&copy, elem);
		lst = lst->next;
	}
	return (copy);
}
