/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:18:14 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/26 21:10:44 by pmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_argument(char **argv, int i)
{
	printf("%s", argv[i]);
	if (argv[i + 1])
		printf(" ");
}

void	builtin_echo(void *data, int pos)
{
	t_system	*sys;
	char		**argv;
	int			i;
	size_t		j;
	int			has_return;

	has_return = 1;
	sys = (t_system *)data;
	argv = sys->cmds[pos].argv;
	i = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", ft_strlen("-n")))
	{
		j = 1;
		while (argv[i][j] && argv[i][j] == 'n')
			j++;
		if (j != ft_strlen(argv[i]) && argv[i][j] != 'n')
			break ;
		has_return = 0;
		i++;
	}
	while (argv[i])
		print_argument(argv, i++);
	if (has_return)
		printf("\n");
}
