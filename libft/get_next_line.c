/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:48:19 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/12 10:03:07 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list_c	*stash[OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_add_tostash(fd, &stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	extract_line(stash[fd], &line);
	clean_stash(&stash[fd]);
	if (line[0] == '\0')
	{
		free_stash(stash[fd]);
		stash[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_add_tostash(int fd, t_list_c **stash)
{
	char	*buf;
	int		ch7al_read;

	ch7al_read = 1;
	while (!found_nl(*stash) && ch7al_read != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		ch7al_read = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && ch7al_read == 0) || ch7al_read == -1)
		{
			free(buf);
			return ;
		}
		buf[ch7al_read] = '\0';
		add_buf_to_stash(stash, buf, ch7al_read);
		free(buf);
	}
}

void	allocate_line(t_list_c *stash, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	extract_line(t_list_c *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	allocate_line(stash, line);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list_c **stash)
{
	t_list_c	*last;
	t_list_c	*node;
	int			i;
	int			j;

	node = malloc(sizeof(t_list_c));
	if (stash == NULL || node == NULL)
		return ;
	node->next = NULL;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] == '\n')
		i++;
	node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		node->content[j++] = last->content[i++];
	node->content[j] = '\0';
	free_stash(*stash);
	*stash = node;
}
