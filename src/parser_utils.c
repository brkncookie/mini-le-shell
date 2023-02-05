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
		if (tkn->type & (VAR | WORD) || (tkn->type & WHITE_SPC
				&& tkn->stat & (IN_DQUOTE | IN_QUOTE)))
		{
			if (!flag && (tkn->stat & (IN_DQUOTE | IN_QUOTE) && cnt++))
				flag = 1;
			else if (flag && !(tkn->stat & (IN_DQUOTE | IN_QUOTE)))
				flag = 0;
			else if (!(flag && (tkn->stat & (IN_DQUOTE | IN_QUOTE))))
				cnt++;
		}
		tkn = tkn->next;
	}
	return (cnt);
}

char	**fill_arg(t_tkns *tkn, char **arg, int i)
{
	char	*str;
	int		len;

	len = 0;
	str = tkn->val;
	if (!(tkn->stat & (IN_DQUOTE | IN_QUOTE)))
		len = tkn->len;
	if (tkn->stat & (IN_DQUOTE | IN_QUOTE))
	{
		while (tkn && (tkn->stat & (IN_DQUOTE | IN_QUOTE)))
		{
			len += tkn->len;
			tkn = tkn->next;
		}
	}
	/* replace strndup with ft_strndup */
	arg[i] = strndup(str, len);
	if (!arg[i])
		return (NULL);
	return (arg);
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
		if (tkn->type & (VAR | WORD) || (tkn->type & WHITE_SPC
				&& tkn->stat & (IN_DQUOTE | IN_QUOTE)))
			if (!(fill_arg(tkn, arg, i++)))
				return (*error = 1, arg);
		tkn = tkn->next;
	}
	arg[i] = NULL;
	return (arg);
}
