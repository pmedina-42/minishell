/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:04:46 by pmedina-          #+#    #+#             */
/*   Updated: 2021/09/16 20:44:17 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"
# define NAME "minishell: "
# define READ_END 0
# define WRITE_END 1
# define PROMPT "mini $> "
# define TO_JOIN "TO\aJOIN"

# define YELLOW    "\033[1;33m"
# define GREEN    "\033[1;32m"
# define BLUE    "\033[1;34m"
# define PINK    "\033[1;35m"
# define GRAY    "\033[1;30m"
# define CYAN    "\033[1;36m"
# define RED    "\033[1;31m"
# define WHITE    "\033[0;37m"

typedef void	(*t_function)(void *, int);

typedef struct s_command
{
	char		*cmd;
	char		*pre_cmd;
	char		**argv;
	int			is_firts;
	char		*file_in;
	char		*file_out;
	int			fd_in;
	int			fd_out;
	int			fd[2];
	int			fd_lim[2];
	char		*limiter;
	int			to_append;
	t_function	builtin;
	int			error;
	int			pid;
	int			pid_limiter;
}	t_command;

typedef struct s_system
{
	t_command	*cmds;
	int			nbr_cmds;
	char		**paths;
	t_list		*list_env;
	char		**env;
	int			error;
	int			error_cmd;
}	t_system;

void		load_environment(t_system *sys, char **env);
void		reload_environment(t_system *sys);
void		free_split(char **split);
void		delete_str(void *str);
char		*get_value_env(t_system *sys, char *name);
t_list		*get_node_env(t_system *sys, char *name);
void		delete_value_env(t_system *sys, char *name);
void		show_error(t_system *sys, char *str);
void		show_error_command(t_system *sys, char *resource);
void		check_malloc(t_system *sys, void *reserved);
void		clean_line(t_system *sys);
void		exec_line(t_system *sys, const char *line);
void		check_files(t_system *sys, t_command *cmd);
void		save_command(t_system *sys, t_command *cmd, char *argv);
void		add_path(t_system *sys, t_command *cmd);
int			load_path(t_system *sys);
t_list		*load_argv(t_command *cmd);
void		run_commands(t_system *sys);
int			jump_quotes(const char *str, int pos);
void		find_files(t_system *sys, t_command *cmd);
void		run_limitator(t_system *sys, t_command *cmd);
void		ctrl_c_signal(int i_signal);
void		ctrl_slash_signal(int i_signal);
t_list		*array_to_list(char **array);
char		**list_to_array(t_list *lst);
char		*list_to_str(t_list *lst);
void		interpret_argv(t_system *sys, t_list *lst);
t_function	is_builtin(char *cmd);
void		run_builtin(t_system *sys, int pos);
int			is_builtin_without_process(t_system *sys);
size_t		ft_maxlen(char *str1, char *str2);
char		**find_env_arr(char **envarr, char *search);
void		builtin_pwd(void *data, int pos);
void		builtin_env(void *data, int pos);
void		builtin_cd(void *data, int pos);
void		builtin_export(void *data, int pos);
void		builtin_unset(void *data, int pos);
void		builtin_echo(void *data, int pos);
void		builtin_exit(void *data, int pos);
t_list		*copy_and_sort_env(t_list *env);
void		print_header(void);
void		str_replace(char **str, const char *s1, const char *s2);
int			load_word(char *str, int size, t_list **lst);
void		find_path(t_system *sys, t_command *cmd);
void		wait_process(t_system *sys);
char		**list_to_array_pars(t_list *lst);
t_list		*split_argv(char *str, t_list *lst);
int			pos_invalid_char(const char *str);
#endif
