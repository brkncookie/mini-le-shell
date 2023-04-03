/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:39:31 by mnadir            #+#    #+#             */
/*   Updated: 2023/04/03 15:06:28 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	ft_isspace(char c)
{
	return (c == '\n' || c == '\r' || c == '\f' \
			|| c == '\t' || c == '\v' || c == ' ');
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strndup(const char *s1, size_t l)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s1);
	if (len < l)
		l = len;
	p = ft_calloc(l + 1, sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, l);
	return (p);
}

void	freeredr(t_tree *tree)
{
	if (!tree)
		return ;
	freeredr(tree->redr);
	free(tree->limn);
	free(tree);
}

void	freetree(t_tree *tree)
{
	int	i;

	i = 0;
	if (!tree)
		return ;
	freetree(tree->limn);
	freetree(tree->lisr);
	while (tree->arg && tree->arg[i])
		free(tree->arg[i++]);
	if (tree->redr)
		freeredr(tree->redr);
	free(tree->arg);
	free(tree);
}
