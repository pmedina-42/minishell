/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:49:46 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/09/14 22:19:04 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_char(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}

static char	*save_variable(t_system *sys, const char *str, t_list **lst)
{
	char	*temp;
	int		i;

	i = 0;
	if (str[i + 1] == '?')
		ft_lstadd_back(lst, ft_lstnew(get_value_env(sys, "?")));
	if (ft_isdigit(str[i + 1]) || str[i + 1] == '?')
		return ((char *)&str[i + 2]);
	if (str[i + 1] && !ft_strchr(" \t\v\f\n", str[i + 1]))
	{
		str = &str[i + 1];
		i = pos_invalid_char(str);
		if (i < 0)
			i = ft_strlen(str);
		temp = ft_strndup(str, i);
		ft_lstadd_back(lst, ft_lstnew(get_value_env(sys, temp)));
		free(temp);
		return ((char *)&str[i]);
	}
	else
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup("$")));
		return ((char *)&str[i + 1]);
	}
}

static char	*replace_variable(t_system *sys, const char *str)
{
	char	*temp;
	int		i;
	t_list	*lst;

	lst = 0;
	while (ft_strchr(str, '$'))
	{
		i = find_char(str, '$');
		if (i > 0)
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(str, i)));
		str = save_variable(sys, &str[i], &lst);
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(str)));
	temp = list_to_str(lst);
	ft_lstclear(&lst, delete_str);
	str_replace(&temp, "\\\"", "\"");
	str_replace(&temp, "\\'", "'");
	return (temp);
}

void	interpret_argv(t_system *sys, t_list *lst)
{
	int		len;
	char	*temp;
	char	*str;

	while (lst)
	{
		temp = (char *)lst->content;
		len = ft_strlen(temp);
		if (len > 1 && temp[0] == '"' && temp[len - 1] == '"')
		{
			temp = ft_strndup(&temp[1], len - 2);
			str = replace_variable(sys, temp);
			free(temp);
		}
		else if (temp[0] != '\'' || temp[len - 1] != '\'')
			str = replace_variable(sys, temp);
		else
			str = ft_strndup(&temp[1], len - 2);
		free((char *)lst->content);
		lst->content = str;
		lst = lst->next;
	}
}
