/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:39:31 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/24 11:51:09 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

int	ft_isspace(char c)
{
	return (c == '\n' || c == '\r' || c == '\f' \
			|| c == '\t' || c == '\v' || c == ' ');
}

void	freelst(t_tkns **lst)
{
	t_tkns	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		(*lst) = tmp;
	}
}

void	freetree(t_tree *tree)
{
	if (!tree)
		return ;
	freetree(tree->limn);
	freetree(tree->lisr);
	free(tree);
}

