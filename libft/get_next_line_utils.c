/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:48:25 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/12 10:03:35 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_nl(t_list_c *stash)
{
	t_list_c	*last;
	int			i;

	if (!stash)
		return (0);
	last = ft_lstlast(stash);
	i = 0;
	while (last->content[i])
	{
		if (last->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list_c	*ft_lstlast(t_list_c *lst)
{
	t_list_c	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_buf_to_stash(t_list_c **stash, char *buff, int ch7al_read)
{
	t_list_c	*new_node;
	t_list_c	*last;
	int			i;

	new_node = malloc(sizeof(t_list_c));
	if (new_node == NULL)
		return ;
	new_node->content = malloc(sizeof(char) * (ch7al_read + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < ch7al_read)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	new_node->next = NULL;
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lstlast(*stash);
	last->next = new_node;
}

void	free_stash(t_list_c *stash)
{
	t_list_c	*tmp;

	if (!stash)
		return ;
	while (stash)
	{
		tmp = (stash)->next;
		free((stash)->content);
		free(stash);
		stash = tmp;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
