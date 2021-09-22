/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:50:15 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/09/22 20:09:28 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*try_load(char *str, t_list **lst, const char *s1, const char *s2)
{
	size_t	i;

	if (*str)
	{
		i = 0;
		while (s1[i] && str[i] == s1[i])
			i++;
		if (i == ft_strlen(s1))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(s2)));
			return (&str[i]);
		}
		ft_lstadd_back(lst, ft_lstnew(ft_strndup(str, i - 1)));
		return (&str[i]);
	}
	return (str);
}

void	str_replace(char **str, const char *s1, const char *s2)
{
	t_list	*lst;
	int		i;
	char	*temp;

	lst = 0;
	temp = *str;
	i = 0;
	while (temp[i])
	{
		while (temp[i] && temp[i] != s1[0])
			i++;
		if (i > 0)
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(temp, i)));
		temp = &temp[i];
		temp = try_load(temp, &lst, s1, s2);
		i = 0;
	}
	temp = *str;
	*str = list_to_str(lst);
	ft_lstclear(&lst, delete_str);
	free(temp);
}

char	*list_to_str(t_list *lst)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (lst)
	{
		temp = ft_strjoin(str, (char *)lst->content);
		free(str);
		str = temp;
		lst = lst->next;
	}
	return (str);
}

void	delete_str(void *str)
{
	char	*del;

	del = (char *)str;
	free(del);
}

int	pos_invalid_char(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		if (ft_isdigit(str[i]))
			return (0);
		while (str[i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (i);
			i++;
		}
	}
	return (-1);
}
