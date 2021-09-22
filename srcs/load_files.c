/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:26:24 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/20 17:43:22 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	jump_quotes(const char *str, int pos)
{
	int	c;
	int	i;

	i = pos;
	if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != 92))
	{
		c = str[i];
		i++;
		while (str[i] && (str[i] != c || (str[i] == '"' && str[i - 1] == 92)))
			i++;
		if (!str[i])
			return (pos);
	}
	return (i);
}

static void	remove_and_load(t_system *sys, char **save_in, char *file)
{
	t_list	*lst;
	char	**words;

	if (*save_in)
		free(*save_in);
	lst = 0;
	if (file)
	{
		lst = split_argv(file, lst);
		interpret_argv(sys, lst);
		words = list_to_array_pars(lst);
		ft_lstclear(&lst, delete_str);
		lst = array_to_list(words);
		free_split(words);
		*save_in = list_to_str(lst);
		ft_lstclear(&lst, delete_str);
	}
	else
		*save_in = 0;
}

static void	load_option(t_system *sys, char *file, char *opt, t_command *cmd)
{
	if (!ft_strcmp(opt, "<<"))
	{
		remove_and_load(sys, &cmd->limiter, file);
		remove_and_load(sys, &cmd->file_in, 0);
	}
	else if (!ft_strcmp(opt, ">>"))
	{
		remove_and_load(sys, &cmd->file_out, file);
		cmd->to_append = 1;
	}
	else if (!ft_strcmp(opt, "<"))
		remove_and_load(sys, &cmd->file_in, file);
	else if (!ft_strcmp(opt, ">"))
		remove_and_load(sys, &cmd->file_out, file);
	if (ft_strchr(file, '<') || ft_strchr(file, '>'))
	{
		cmd->error = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		if (ft_strchr(file, '<'))
			ft_putchar_fd('<', 2);
		else
			ft_putchar_fd('>', 2);
		ft_putchar_fd('\n', 2);
	}
	check_files(sys, cmd);
}

void	load_file(t_system *sys, char *str, int pos, t_command *cmd)
{
	int		i;
	int		j;
	char	*temp;
	char	option[3];

	i = pos + 1;
	ft_bzero(option, 3);
	option[0] = str[pos];
	if (!ft_strncmp(&str[pos], "<<", 2) || !ft_strncmp(&str[pos], ">>", 2))
	{
		option[1] = str[pos + 1];
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	j = i;
	while (str[j] && !ft_isspace(str[j]))
		j++;
	temp = ft_strndup(&str[i], j - i);
	check_malloc(sys, temp);
	load_option(sys, temp, option, cmd);
	free(temp);
	temp = ft_substrdel(str, pos, j - pos);
	free(cmd->pre_cmd);
	cmd->pre_cmd = temp;
}

void	find_files(t_system *sys, t_command *cmd)
{
	int		i;
	char	*temp;

	temp = cmd->pre_cmd;
	i = 0;
	while (temp[i])
	{
		i = jump_quotes(temp, i);
		if (temp[i] == '<' || temp[i] == '>')
		{
			load_file(sys, temp, i, cmd);
			temp = cmd->pre_cmd;
			i = 0;
		}
		i++;
	}
}
