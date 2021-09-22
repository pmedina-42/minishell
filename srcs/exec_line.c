/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:36:00 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/21 18:09:19 by lgomez-d         ###   ########.fr       */
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

char	*get_cmd_line(t_system *sys, const char *line, t_command *cmd)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '|')
	{
		i = jump_quotes(line, i);
		i++;
	}
	cmd->pre_cmd = ft_strndup(line, i);
	check_malloc(sys, cmd->pre_cmd);
	add_path(sys, cmd);
	pipe(cmd->fd);
	if (!line[i])
		return (NULL);
	return ((char *)&line[i + 1]);
}

void	load_cmds(t_system *sys, const char *line)
{
	int	i;

	i = 0;
	while (i < sys->nbr_cmds && line)
	{
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
	run_commands(sys);
}
