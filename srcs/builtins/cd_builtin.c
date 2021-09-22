/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:49:21 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/21 21:32:18 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_dir(t_system *sys, int pos, char *dest, char *route)
{
	if (chdir(dest) == -1)
	{
		sys->error_cmd = 1;
		if (ft_strncmp(route, "HOME", 4) == 0 || ft_strncmp(route, "PWD", 3) \
			== 0 || ft_strncmp(route, "OLDPWD", 6) == 0)
		{
			ft_putstr_fd(NAME, 2);
			ft_putstr_fd(*sys->cmds[pos].argv, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(route, 2);
			ft_putendl_fd(" not set", 2);
		}
		else
			show_error(sys, route);
	}
}

static void	*get_n_set_paths(t_system *sys, char *oldpwd)
{
	char	*newpath;
	t_list	*pwdlst;
	t_list	*oldpwdlst;

	newpath = getcwd(NULL, 0);
	pwdlst = get_node_env(sys, "PWD");
	oldpwdlst = get_node_env(sys, "OLDPWD");
	if (pwdlst)
	{
		free(pwdlst->content);
		pwdlst->content = ft_strjoin("PWD=", newpath);
	}
	if (oldpwdlst)
	{
		free(oldpwdlst->content);
		oldpwdlst->content = ft_strjoin("OLDPWD=", oldpwd);
	}
	else
		ft_lstadd_back(&sys->list_env,
			ft_lstnew(ft_strjoin("OLDPWD=", oldpwd)));
	free(newpath);
	return (0);
}

static void	check_virgulilla_route(t_system *sys, char *argv, int pos)
{
	char	*route;
	char	*home;

	home = "/Users/";
	route = ft_strjoin(home, argv);
	change_dir(sys, pos, route, --argv);
	free(route);
}

static void	*check_cd_argv(t_system *sys, char *argv, char *dir, int pos)
{
	if (!argv || ft_strncmp(argv, "--", ft_maxlen(argv, "--")) == 0
		|| ft_strncmp(argv, "~", ft_maxlen(argv, "~")) == 0)
	{
		dir = get_value_env(sys, "HOME");
		change_dir(sys, pos, dir, "HOME");
	}
	else if (ft_strncmp(argv, "-", 1) == 0)
	{
		dir = get_value_env(sys, "OLDPWD");
		change_dir(sys, pos, dir, "OLDPWD");
	}
	else if (argv[0] == '~')
	{
		check_virgulilla_route(sys, ++argv, pos);
	}
	else
	{
		change_dir(sys, pos, argv, argv);
	}
	free(dir);
	return (0);
}

void	builtin_cd(void *data, int pos)
{
	t_system	*sys;
	char		**argv;
	char		*oldpwd;
	char		*dir;

	sys = (t_system *)data;
	argv = sys->cmds[pos].argv;
	oldpwd = getcwd(NULL, 0);
	dir = 0;
	check_cd_argv(sys, argv[1], dir, pos);
	get_n_set_paths(sys, oldpwd);
	free(oldpwd);
}
