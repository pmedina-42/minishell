/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:36:00 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/28 15:54:28 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_comands(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (line[i])
	{
		i = jump_quotes(line, i);
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

static char	*throw_error(t_system *sys)
{
	sys->error_cmd = 258;
	sys->error = 1;
	ft_putendl_fd("minishell: syntax error near unexpected token '|'", 2);
	return (0);
}

char	*get_cmd_line(t_system *sys, const char *line, t_command *cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '|')
	{
		i = jump_quotes(line, i);
		i++;
	}
	str = ft_strndup(line, i);
	cmd->pre_cmd = ft_strtrim(str, " \t\n\v\f\r");
	free(str);
	if (ft_strlen(cmd->pre_cmd))
	{
		check_malloc(sys, cmd->pre_cmd);
		add_path(sys, cmd);
		if (!line[i])
			return (NULL);
		return ((char *)&line[i + 1]);
	}
	else
		return (throw_error(sys));
}

void	load_cmds(t_system *sys, const char *line)
{
	int	i;

	i = 0;
	while (i < sys->nbr_cmds && line)
	{
		sys->cmds[i].nbr = i;
		line = get_cmd_line(sys, line, &sys->cmds[i]);
		i++;
	}
}

void	exec_line(t_system *sys, const char *line)
{
	extern int	g_exec_child;

	g_exec_child = 3;
	sys->nbr_cmds = count_comands(line);
	sys->cmds = (t_command *)ft_calloc(sizeof(t_command), sys->nbr_cmds);
	check_malloc(sys, sys->cmds);
	load_cmds(sys, line);
	if (!sys->error)
		run_commands(sys);
}
