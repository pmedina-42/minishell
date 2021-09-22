/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:24:07 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/21 22:47:14 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*array_to_list(char **array)
{
	int		i;
	t_list	*lst;

	lst = 0;
	if (array)
	{
		i = 0;
		while (array[i])
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(array[i])));
			i++;
		}
		return (lst);
	}
	else
		return (0);
}

int	join_nodes(t_list *lst)
{
	t_list	*next;
	char	*temp;

	if (lst->next && lst->next->next \
		&& !ft_strcmp((char *)lst->next->content, TO_JOIN))
	{
		next = lst->next->next->next;
		temp = ft_strjoin((char *)lst->content, \
			(char *)lst->next->next->content);
		free((char *)lst->content);
		lst->content = temp;
		ft_lstdelone(lst->next->next, delete_str);
		ft_lstdelone(lst->next, delete_str);
		lst->next = next;
		return (0);
	}
	return (1);
}

char	**list_to_array_pars(t_list *lst)
{
	int		size;
	int		i;
	char	**array;

	size = ft_lstsize(lst);
	array = (char **)ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (lst)
	{
		if (join_nodes(lst))
		{
			array[i] = ft_strdup((char *)lst->content);
			i++;
			lst = lst->next;
		}
	}
	return (array);
}

char	**list_to_array(t_list *lst)
{
	int		size;
	int		i;
	char	**array;

	size = ft_lstsize(lst);
	array = (char **)ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (lst)
	{
		if (ft_strlen((char *)lst->content))
		{
			array[i] = ft_strdup((char *)lst->content);
			i++;
		}
		lst = lst->next;
	}
	return (array);
}
