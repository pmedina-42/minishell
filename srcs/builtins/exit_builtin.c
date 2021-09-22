/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmedina- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:36:23 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/22 21:10:21 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	show_exit_error(t_system *sys, char **argv, int i)
{
	if (i == 0)
	{
		sys->error_cmd = 1;
		ft_putstr_fd(NAME, 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("too many arguments", 2);
	}
	else
	{
		ft_putstr_fd(NAME, 2), ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("numeric argument required", 2);
		exit (255);
	}
}

static int	check_exit_argv(char *argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[1]) != 0)
			break ;
		i++;
	}
	if (i == ft_strlen(argv))
		return (1);
	return (0);
}

void	builtin_exit(void *data, int pos)
{
	t_system	*sys;
	char		**argv;

	sys = (t_system *)data;
	argv = sys->cmds[pos].argv;
	printf("exit\n");
	if (ft_array_len((void **)argv) >= 3)
	{
		if (!check_exit_argv(argv[1]))
			show_exit_error(sys, argv, 0);
		else
			show_exit_error(sys, argv, 1);
	}
	else if (ft_array_len((void **)argv) == 2)
	{
		if (check_exit_argv(argv[1]))
			show_exit_error(sys, argv, 1);
		else
			exit (ft_atoi(argv[1]));
	}
	else
		exit (0);
}
