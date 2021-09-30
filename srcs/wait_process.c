/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:21:19 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/09/28 18:07:38 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_command	*get_cmd(t_system *sys, int pid)
{
	int	i;

	i = 0;
	if (pid > 0)
	{
		while (i < sys->nbr_cmds)
		{
			if (sys->cmds[i].pid == pid)
				return (&sys->cmds[i]);
			i++;
		}
	}
	return (0);
}

static void	check_status(t_system *sys, t_command *cmd, int status)
{
	if (!WIFEXITED(status))
		sys->error_cmd = 130;
	else if (WIFEXITED(status) && !cmd->error)
		sys->error_cmd = WEXITSTATUS(status);
	else if (cmd->error && !sys->error_cmd)
		sys->error_cmd = 1;
	else if (!cmd->error)
		sys->error_cmd = 0;
}

void	close_fds(t_system *sys)
{
	int	i;

	i = 0;
	while (i < sys->nbr_cmds)
	{
		if (sys->cmds[i].fd[READ_END] > 1)
			close(sys->cmds[i].fd[READ_END]);
		if (sys->cmds[i].fd[WRITE_END] > 1)
			close(sys->cmds[i].fd[WRITE_END]);
		i++;
	}
}

void	wait_process(t_system *sys)
{
	int			pid;
	int			status;
	t_command	*cmd;
	extern int	g_exec_child;

	pid = 1;
	close_fds(sys);
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		cmd = get_cmd(sys, pid);
		if (cmd)
		{
			if (!cmd->nbr && !WIFEXITED(status) && g_exec_child < 0)
				printf("Quit: 3\n");
			if (!WIFEXITED(status) && g_exec_child < 0)
				sys->error_cmd = 131;
			else if (cmd->nbr == sys->nbr_cmds - 1)
				check_status(sys, cmd, status);
		}
	}
}
