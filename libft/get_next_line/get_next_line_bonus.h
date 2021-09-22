/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:56:52 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/02/11 11:39:33 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_listc
{
	char			*str;
	struct s_listc	*next;
}	t_listc;

typedef struct s_datalst
{
	int					fd;
	t_listc				*firts;
	t_listc				*last;
	long				len;
	struct s_datalst	*next;
}	t_datalst;

typedef struct s_fds
{
	t_datalst	*fds;
	t_datalst	*select;
}	t_fds;

int		get_next_line(int fd, char **line);
t_listc	*ft_new_elem(t_datalst *data);
void	ft_list_clear(t_fds *fds, int fd);
void	ft_delete_front(t_datalst *data);

#endif
