/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:01:20 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/09/21 19:42:48 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	load_in(t_system *sys, int pos)
{
	t_command	cmd;
	int			fd;

	cmd = sys->cmds[pos];
	if (cmd.limiter && !cmd.file_in)
	{
		close(cmd.fd_lim[WRITE_END]);
		dup2(cmd.fd_lim[READ_END], STDIN_FILENO);
		close(cmd.fd_lim[READ_END]);
	}
	else if (cmd.file_in)
	{
		fd = open(cmd.file_in, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (pos > 0)
	{
		close(sys->cmds[pos - 1].fd[WRITE_END]);
		dup2(sys->cmds[pos - 1].fd[READ_END], STDIN_FILENO);
		close(sys->cmds[pos - 1].fd[READ_END]);
	}
}

static void	load_out(t_system *sys, int pos)
{
	t_command	*cmd;
	int			fd;

	cmd = &sys->cmds[pos];
	if (!cmd->error && cmd->file_out)
	{
		if (!cmd->to_append)
			fd = open(cmd->file_out, O_CREAT | O_WRONLY | \
			O_TRUNC | O_APPEND, 0644);
		else
			fd = open(cmd->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (pos < sys->nbr_cmds - 1)
	{
		close(cmd->fd[READ_END]);
		dup2(cmd->fd[WRITE_END], STDOUT_FILENO);
		close(cmd->fd[WRITE_END]);
	}
}

static void	run_child(t_system *sys, int pos)
{
	t_command	*cmd;
	extern int	g_exec_child;

	g_exec_child = 1;
	cmd = &sys->cmds[pos];
	load_in(sys, pos);
	load_out(sys, pos);
	if (!cmd->error && cmd->argv)
	{
		if (!cmd->builtin)
		{
			execve(cmd->cmd, cmd->argv, sys->env);
			show_error(sys, "Error in exec");
			exit(1);
		}
		run_builtin(sys, pos);
		if (cmd->error && !sys->error_cmd)
			exit(1);
		else if (cmd->error && sys->error_cmd)
			exit(sys->error_cmd);
	}
	exit(0);
}

static void	close_fds(t_system *sys, int pos, int pid)
{
	sys->cmds[pos].pid = pid;
	close(sys->cmds[pos].fd[WRITE_END]);
	if (pos > 0 && pos < sys->nbr_cmds)
		close(sys->cmds[pos - 1].fd[READ_END]);
	if (pos == sys->nbr_cmds - 1)
		close(sys->cmds[pos].fd[READ_END]);
	if (sys->cmds[pos].limiter)
		close(sys->cmds[pos].fd_lim[READ_END]);
}

void	run_commands(t_system *sys)
{
	pid_t		pid;
	int			i;
	extern int	g_exec_child;

	if (!is_builtin_without_process(sys))
	{
		i = 0;
		while (i < sys->nbr_cmds && g_exec_child != 2)
		{
			run_limitator(sys, &sys->cmds[i]);
			signal(SIGQUIT, ctrl_slash_signal);
			find_path(sys, &sys->cmds[i]);
			g_exec_child = 4;
			pid = fork();
			if (pid == -1)
				show_error(sys, "Error in fork");
			if (pid == 0)
				run_child(sys, i);
			else
				close_fds(sys, i, pid);
			i++;
		}
	}
	wait_process(sys);
}
