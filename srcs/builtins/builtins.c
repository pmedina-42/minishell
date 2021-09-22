/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 21:45:33 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/14 20:04:37 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_maxlen(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 < len2)
		return (len2);
	return (len1);
}

static int	check_cd_exit(t_command *cmd, t_system *sys)
{
	if (cmd->builtin && cmd->builtin == builtin_exit)
	{
		builtin_exit(sys, 0);
		return (1);
	}
	if (cmd->builtin && cmd->builtin == builtin_cd)
	{
		builtin_cd(sys, 0);
		return (1);
	}
	return (0);
}

int	is_builtin_without_process(t_system *sys)
{
	t_command	*cmd;

	if (sys->nbr_cmds == 1)
	{
		cmd = &sys->cmds[0];
		if (cmd->builtin && cmd->builtin == builtin_export)
		{
			builtin_export(sys, 0);
			return (1);
		}
		if (cmd->builtin && cmd->builtin == builtin_unset)
		{
			builtin_unset(sys, 0);
			return (1);
		}
		if (check_cd_exit(cmd, sys) == 1)
			return (1);
	}
	return (0);
}

t_function	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_maxlen(cmd, "echo")))
		return (builtin_echo);
	if (!ft_strncmp(cmd, "export", ft_maxlen(cmd, "export")))
		return (builtin_export);
	if (!ft_strncmp(cmd, "env", ft_maxlen(cmd, "env")))
		return (builtin_env);
	if (!ft_strncmp(cmd, "unset", ft_maxlen(cmd, "unset")))
		return (builtin_unset);
	if (!ft_strncmp(cmd, "pwd", ft_maxlen(cmd, "pwd")))
		return (builtin_pwd);
	if (!ft_strncmp(cmd, "cd", ft_maxlen(cmd, "cd")))
		return (builtin_cd);
	if (!ft_strncmp(cmd, "exit", ft_maxlen(cmd, "exit")))
		return (builtin_exit);
	return (0);
}

void	run_builtin(t_system *sys, int pos)
{
	t_command	*cmd;

	cmd = &sys->cmds[pos];
	cmd->builtin((void *)sys, pos);
}
