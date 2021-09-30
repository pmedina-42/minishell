/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:10:00 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/28 16:30:37 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_signal(int i_signal)
{
	extern int	g_exec_child;

	if (i_signal == SIGINT && !g_exec_child)
	{
		g_exec_child = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
	else if (i_signal == SIGINT && g_exec_child == 1)
	{
		printf("\n");
		exit(130);
	}
	else if (i_signal == SIGINT && g_exec_child >= 3)
	{
		printf("\n");
		g_exec_child = 2;
	}
	else if (i_signal == SIGINT && g_exec_child == -2)
		exit (1);
}

void	ctrl_slash_signal(int i_signal)
{
	extern int	g_exec_child;

	if (i_signal == SIGQUIT && g_exec_child == 4)
		g_exec_child = -1;
}
