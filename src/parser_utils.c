/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:07:57 by alemsafi          #+#    #+#             */
/*   Updated: 2023/02/05 11:08:09 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <string.h>

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
	int	i;

	i = 0;
	if (!tree)
		return ;
	freetree(tree->limn);
	freetree(tree->lisr);
	while (tree->arg && tree->arg[i])
		free(tree->arg[i++]);
	if (tree->redr)
	{
		free(tree->redr->limn);
		free(tree->redr);
	}
	free(tree->arg);
	free(tree);
}

int	count_arg(t_tkns *tkn)
{
	int	cnt;
	int	delim;
	int	flag;

	delim = PIPE | AND | OR | HERE_DOC | APPEND | REDR_O | REDR_I;
	cnt = 0;
	flag = 0;
	while (tkn && !(tkn->type & delim))
	{
		if (tkn->type & (VAR | WORD))
			cnt++;
		tkn = tkn->next;
	}
	return (cnt);
}

char	**get_arg(t_tkns *tkn, int *error)
{
	char	**arg;
	int		delim;
	int		i;
	int		cnt;

	delim = PIPE | AND | OR | HERE_DOC | APPEND | REDR_O | REDR_I;
	cnt = count_arg(tkn);
	if (!cnt)
		return (NULL);
	arg = ft_calloc(cnt + 1, sizeof(*arg));
	if (!arg)
		return (*error = 1, NULL);
	i = 0;
	while (tkn && !(tkn->type & delim) && i < cnt)
	{
		if (tkn->type & (VAR | WORD))
		{
			arg[i] = ft_strndup(tkn->val, tkn->len);
			if (!arg[i])
				return (*error = 1, NULL);
			i++;
		}
		tkn = tkn->next;
	}
	return (arg[i] = NULL, arg);
}
