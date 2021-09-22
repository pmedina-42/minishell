/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:36:23 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/21 21:25:04 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(void *data, int pos)
{
	char	*str;

	(void)data;
	(void)pos;
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
}

void	builtin_unset(void *data, int pos)
{
	char		**argv;
	t_system	*sys;
	int			i;

	sys = (t_system *)data;
	argv = sys->cmds[pos].argv;
	i = 0;
	while (argv[++i])
		delete_value_env(sys, argv[i]);
}

void	builtin_env(void *data, int pos)
{
	t_system	*sys;
	t_command	*cmd;
	t_list		*lst;

	sys = (t_system *)data;
	cmd = &sys->cmds[pos];
	lst = sys->list_env;
	if (ft_array_len((void **)cmd->argv) == 1)
	{
		while (lst)
		{
			if (ft_strchr(lst->content, '=') != 0)
				printf("%s\n", (char *)lst->content);
			lst = lst->next;
		}
	}
	if (ft_array_len((void **)cmd->argv) > 1)
	{
		sys->error_cmd = 1;
		show_error(sys, cmd->argv[1]);
	}
}
