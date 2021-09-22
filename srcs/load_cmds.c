/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:29:55 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/20 20:06:08 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	load_word(char *str, int size, t_list **lst)
{
	int		count;
	char	*temp;

	if (!size)
	{
		count = jump_quotes(str, 0);
		if (count)
		{
			temp = ft_strndup(str, count + 1);
			ft_lstadd_back(lst, ft_lstnew(temp));
			return (count + 1);
		}
		return (1);
	}
	else
	{
		temp = ft_strndup(str, size);
		ft_lstadd_back(lst, ft_lstnew(temp));
		return (size);
	}
	return (0);
}

t_list	*split_argv(char *str, t_list *lst)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (jump_quotes(str, i) != i || ft_isspace(str[i]))
		{
			i = load_word(str, count, &lst);
			if (i > 1 && str[i] && str[i] != ' ')
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(TO_JOIN)));
			count = -1;
			while (ft_isspace(str[i]))
				i++;
			str = &str[i];
			i = -1;
		}
		count++;
		i++;
	}
	load_word(str, count, &lst);
	return (lst);
}

t_list	*load_argv(t_command *cmd)
{
	t_list	*lst;

	lst = 0;
	lst = split_argv(cmd->pre_cmd, lst);
	return (lst);
}

int	load_path(t_system *sys)
{
	char	*str;

	if (sys->paths)
		free_split(sys->paths);
	sys->paths = 0;
	str = get_value_env(sys, "PATH");
	if (ft_strlen(str))
	{
		sys->paths = ft_split(str, ':');
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
