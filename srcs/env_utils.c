/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:24:30 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/22 21:14:32 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	load_environment(t_system *sys, char **env)
{
	char		*s;
	char		*tmp;
	t_list		*lst;

	sys->list_env = array_to_list(env);
	if (!sys->list_env)
	{
		s = getcwd(NULL, 0);
		ft_lstadd_back(&sys->list_env, ft_lstnew(ft_strjoin("PWD=", s)));
		ft_lstadd_back(&sys->list_env, ft_lstnew(ft_strdup("OLDPWD")));
		ft_lstadd_back(&sys->list_env, ft_lstnew(ft_strdup("SHLVL=1")));
		free(s);
	}
	else
	{
		s = get_value_env(sys, "SHLVL");
		free(s);
		s = ft_itoa(ft_atoi(s) + 1);
		tmp = ft_strjoin("SHLVL=", s);
		free(s);
		lst = get_node_env(sys, "SHLVL");
		free((char *)lst->content);
		lst->content = (char *)tmp;
	}
	sys->env = list_to_array(sys->list_env);
}

void	reload_environment(t_system *sys)
{
	if (sys->env)
		free_split(sys->env);
	sys->env = list_to_array(sys->list_env);
}

char	*get_value_env(t_system *sys, char *name)
{
	char	*temp;
	char	*value;
	int		size;
	t_list	*lst;

	if (ft_strlen(name) == 1 && name[0] == '?')
		return (ft_itoa(sys->error_cmd));
	lst = sys->list_env;
	temp = ft_strjoin(name, "=");
	size = ft_strlen(temp);
	value = 0;
	while (lst && !value)
	{
		value = ft_strnstr((const char *)lst->content, temp, size);
		lst = lst->next;
	}
	free(temp);
	if (value)
		return (ft_strdup(&value[size]));
	else
		return (ft_strdup(""));
}

t_list	*get_node_env(t_system *sys, char *name)
{
	char	*value;
	int		size;
	t_list	*lst;

	lst = sys->list_env;
	size = ft_strlen(name);
	value = 0;
	while (lst && !value)
	{
		value = ft_strnstr((const char *)lst->content, name, size);
		if (value)
			return (lst);
		lst = lst->next;
	}
	return (0);
}

void	delete_value_env(t_system *sys, char *name)
{
	t_list	*lst;
	t_list	*aux;
	int		len;

	len = ft_strlen(name);
	lst = sys->list_env;
	aux = 0;
	while (lst)
	{
		if (!ft_strncmp((char *)lst->content, name, len))
		{
			if (aux)
				aux->next = lst->next;
			else
				sys->list_env = lst->next;
			ft_lstdelone(lst, delete_str);
			lst = 0;
		}
		else
		{
			aux = lst;
			lst = lst->next;
		}
	}
}
