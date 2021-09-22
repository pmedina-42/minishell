/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:18:14 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/20 21:05:32 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(void *data, int pos)
{
	t_system	*sys;
	char		**argv;
	int			i;
	int			has_return;

	has_return = 1;
	sys = (t_system *)data;
	argv = sys->cmds[pos].argv;
	i = 1;
	if (!ft_strcmp(argv[i], "-n"))
	{
		has_return = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (has_return)
		printf("\n");
}
