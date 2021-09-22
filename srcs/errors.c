/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:34:32 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/20 20:24:50 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	show_error(t_system *sys, char *str)
{
	ft_putstr_fd(NAME, 2);
	perror(str);
	sys->error = 1;
}

void	show_error_command(t_system *sys, char *resource)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(resource, 2);
	sys->error_cmd = 127;
	sys->error = 1;
}

void	check_malloc(t_system *sys, void *reserved)
{
	if (!reserved)
	{
		show_error(sys, "Error malloc");
		exit(1);
	}
}

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = 0;
		while (split[i] != 0)
		{
			free(split[i]);
			split[i] = 0;
			i++;
		}
		free(split);
	}
}

void	clean_line(t_system *sys)
{
	extern int	g_exec_child;
	int			i;

	i = 0;
	if (sys->cmds)
	{
		while (i < sys->nbr_cmds)
		{
			free(sys->cmds[i].cmd);
			free(sys->cmds[i].pre_cmd);
			free_split(sys->cmds[i].argv);
			free(sys->cmds[i].file_in);
			free(sys->cmds[i].file_out);
			free(sys->cmds[i].limiter);
			ft_bzero(&sys->cmds[i], sizeof(t_command));
			i++;
		}
		free(sys->cmds);
		sys->cmds = 0;
		sys->nbr_cmds = 0;
	}
	g_exec_child = 0;
	sys->error = 0;
	reload_environment(sys);
	load_path(sys);
}
