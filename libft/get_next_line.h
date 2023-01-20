/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:48:22 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/12 10:02:36 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct a_list
{
	char			*content;
	struct a_list	*next;
}	t_list_c;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char		*get_next_line(int fd);
int			found_nl(t_list_c *stash);
t_list_c	*ft_lstlast(t_list_c *lst);
void		read_add_tostash(int fd, t_list_c **stash);
void		add_buf_to_stash(t_list_c **stash, char *buff, int ch7al_read);
void		allocate_line(t_list_c *stash, char **line);
void		extract_line(t_list_c *stash, char **line);
void		clean_stash(t_list_c **stash);
void		free_stash(t_list_c *stash);
size_t		ft_strlen(const char *str);

#endif
