/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:22:16 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/22 21:08:57 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exec_child;

void	run_program(t_system *sys)
{
	char		*str;
	char		*tmp;

	str = 0;
	tmp = 0;
	while (1)
	{
		free(tmp);
		free(str);
		tmp = 0;
		signal(SIGQUIT, SIG_IGN);
		tmp = readline(PROMPT);
		str = ft_strtrim(tmp, " \t\n\v\f\r");
		if (str && ft_strlen(str))
		{
			add_history(str);
			exec_line(sys, str);
			clean_line(sys);
		}
		else if (str == 0)
		{
			printf("exit\n");
			exit(0);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_system	sys;

	if (argc > 1)
	{
		printf("%s%s: No such file or directory\n", NAME, argv[1]);
		return (0);
	}
	ft_memset(&sys, '\0', sizeof(t_system));
	load_environment(&sys, env);
	load_path(&sys);
	g_exec_child = 0;
	signal(SIGINT, ctrl_c_signal);
	print_header();
	run_program(&sys);
	return (0);
}
