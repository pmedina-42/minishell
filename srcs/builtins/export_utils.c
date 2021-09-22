/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 21:19:10 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/22 21:19:11 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	swap_list_node(t_list *a, t_list *b)
{
	t_list	aux;

	aux.content = a->content;
	a->content = b->content;
	b->content = aux.content;
}

t_list	*copy_and_sort_env(t_list *env)
{
	t_list	*lst;
	t_list	*start;
	t_list	*next;

	lst = 0;
	while (env && env->content)
	{
		ft_lstadd_back(&lst, ft_lstnew(env->content));
		env = env->next;
	}
	start = lst;
	while (lst)
	{
		next = lst->next;
		if (next && ft_strcmp((char *)lst->content, (char *)next->content) > 0)
		{
			swap_list_node(lst, next);
			lst = start;
		}
		else
			lst = lst->next;
	}
	return (start);
}
