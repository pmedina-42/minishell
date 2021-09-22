/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:11:33 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/22 18:06:00 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_process(t_system *sys)
{
	int			i;
	int			status;
	t_command	*cmd;
	extern int	g_exec_child;

	i = 0;
	while (i < sys->nbr_cmds)
	{
		cmd = &sys->cmds[i];
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (!i && !WIFEXITED(status) && !cmd->builtin && g_exec_child < 0)
				printf("Quit: 3\n");
			else if (WIFEXITED(status) && !sys->error)
				sys->error_cmd = WEXITSTATUS(status);
			else if (cmd->error && !sys->error_cmd)
				sys->error_cmd = 1;
			else if (!cmd->error)
				sys->error_cmd = 0;
		}
		if (cmd->pid_limiter)
			waitpid(cmd->pid_limiter, &status, 0);
		i++;
	}
}

static void	redirect_io(t_command *cmd)
{
	close(cmd->fd_lim[READ_END]);
	dup2(cmd->fd_lim[WRITE_END], STDOUT_FILENO);
	close(cmd->fd_lim[WRITE_END]);
}

static void	run_child(t_command *cmd)
{
	t_list	*list;
	t_list	*temp;
	char	*str;

	str = 0;
	list = 0;
	str = readline("> ");
	ft_lstadd_back(&list, ft_lstnew(str));
	while (str && ft_strncmp(str, cmd->limiter, sizeof(str)))
	{
		str = 0;
		str = readline("> ");
		ft_lstadd_back(&list, ft_lstnew(str));
	}
	if (!str)
		printf("\n");
	redirect_io(cmd);
	temp = list;
	while (list->next)
	{
		ft_putendl_fd((char *)list->content, 1);
		list = list->next;
	}
	ft_lstclear(&temp, delete_str);
	exit (0);
}

void	run_limitator(t_system *sys, t_command *cmd)
{
	pid_t		pid;
	extern int	g_exec_child;

	if (cmd->limiter)
	{
		pipe(cmd->fd_lim);
		pid = fork();
		if (pid == -1)
			show_error(sys, "Error in fork");
		else if (pid == 0)
		{
			g_exec_child = 1;
			run_child(cmd);
		}
		else
		{
			close(cmd->fd_lim[WRITE_END]);
			cmd->pid_limiter = pid;
		}
	}
}
