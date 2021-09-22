/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:42:07 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/09/20 20:33:25 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_file_in(t_system *sys, t_command *cmd)
{
	int	fd;

	if (!cmd->error && cmd->file_in)
	{
		fd = open(cmd->file_in, O_RDONLY);
		if (fd < 0)
		{
			show_error(sys, cmd->file_in);
			free(cmd->file_in);
			cmd->file_in = 0;
			cmd->error = 1;
		}
		close(fd);
	}
}

static void	check_file_out(t_system *sys, t_command *cmd)
{
	int	fd;

	if (!cmd->error && cmd->file_out)
	{
		if (!cmd->to_append)
		{
			fd = open(cmd->file_out, O_CREAT | O_WRONLY | \
				O_TRUNC | O_APPEND, 0644);
		}
		else
			fd = open(cmd->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
		{
			show_error(sys, cmd->file_out);
			free(cmd->file_out);
			cmd->file_out = 0;
			cmd->error = 1;
		}
		close(fd);
	}
}

void	check_files(t_system *sys, t_command *cmd)
{
	check_file_in(sys, cmd);
	check_file_out(sys, cmd);
}
