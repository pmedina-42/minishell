/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:08:00 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/28 15:55:46 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_variable(t_system *sys, char *argv, char *s)
{
	t_list	*lst;
	char	*temp;

	temp = ft_strdup(argv);
	lst = get_node_env(sys, s);
	if (lst && ft_strchr(argv, '='))
	{
		free(lst->content);
		lst->content = temp;
	}
	else if (!lst)
		ft_lstadd_back(&sys->list_env, ft_lstnew(temp));
	else
		free(temp);
}

static void	identifier_error(t_system *sys, char **argv, int x)
{
	sys->error_cmd = 1;
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(argv[x], 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static void	no_arg_export(t_system *sys, int y)
{
	char	*str;
	t_list	*lst;
	t_list	*aux;

	lst = copy_and_sort_env(sys->list_env);
	while (lst)
	{
		aux = lst;
		printf("declare -x ");
		str = (char *)aux->content;
		y = 0;
		while (str[y])
		{
			printf("%c", str[y]);
			if (str[y++] == '=')
				printf("\"");
		}
		if (ft_strchr(str, '=') != 0)
			printf("\"");
		printf("\n");
		lst = lst->next;
		free(aux);
	}
}

static void	variable_export(t_system *sys, char **argv, int x, int y)
{
	char	*s;

	while (argv[++x])
	{
		y = 0;
		while (argv[x][y] != '=' && argv[x][y])
			y++;
		s = ft_substr(argv[x], 0, y);
		if (pos_invalid_char(s) == -1 || argv[x][0] == '_')
			check_variable(sys, argv[x], s);
		else
			identifier_error(sys, argv, x);
		free(s);
	}
}

void	builtin_export(void *data, int pos)
{
	char		**argv;
	t_system	*sys;

	sys = (t_system *)data;
	argv = sys->cmds[pos].argv;
	if (!argv[1])
		no_arg_export(sys, 0);
	else
		variable_export(sys, argv, 0, 0);
}
