/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:41:53 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/09/20 20:06:08 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_app(const char *str)
{
	char	*app;

	app = ft_strtrim(str, "/");
	return (app);
}

static int	check_other_path(t_system *sys, t_command *cmd, char **str)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	fd = -1;
	while (sys->paths && sys->paths[i] != 0 && fd < 0)
	{
		free(*str);
		tmp = ft_strjoin(sys->paths[i], "/");
		*str = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		fd = open(*str, O_RDONLY);
		i++;
	}
	return (fd);
}

void	find_path(t_system *sys, t_command *cmd)
{
	int		fd;
	char	*str;

	str = 0;
	fd = -1;
	if (cmd->argv && !cmd->builtin)
	{
		fd = open(cmd->argv[0], O_RDONLY);
		if (fd >= 0 && ft_strlen(cmd->argv[0]))
		{
			str = cmd->argv[0];
			cmd->argv[0] = get_app(str);
		}
		else if (ft_strlen(cmd->argv[0]))
			fd = check_other_path(sys, cmd, &str);
		if (fd >= 0)
			cmd->cmd = str;
		else
		{
			free(str);
			cmd->error = 1;
			show_error_command(sys, cmd->argv[0]);
		}
		close(fd);
	}
}

void	add_path(t_system *sys, t_command *cmd)
{
	t_list	*lst;

	find_files(sys, cmd);
	if (ft_strlen(cmd->pre_cmd))
	{
		lst = load_argv(cmd);
		interpret_argv(sys, lst);
		cmd->argv = list_to_array_pars(lst);
		if (!cmd->argv[0])
		{
			cmd->error = 1;
			return ;
		}
		ft_lstclear(&lst, delete_str);
		if (!cmd->argv)
			show_error(sys, "Malloc does not work");
		cmd->builtin = is_builtin(cmd->argv[0]);
	}
	else
		cmd->error = 1;
}
