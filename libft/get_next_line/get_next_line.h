/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:01:52 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/02/09 20:02:00 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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
	t_listc	*firts;
	t_listc	*last;
	long	len;
}	t_datalst;

int		get_next_line(int fd, char **line);
t_listc	*ft_new_elem(t_datalst *data);
void	ft_list_clear(t_datalst *data);
void	ft_delete_front(t_datalst *data);

#endif
