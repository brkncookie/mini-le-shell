/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:39:31 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/03 09:33:06 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parser.h"
#include <string.h>

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
	int	i;

	i = 0;
	if (!tree)
		return ;
	freetree(tree->limn);
	freetree(tree->lisr);
	while (tree->arg && tree->arg[i])
		free(tree->arg[i++]);
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
	while(tkn && !(tkn->type & delim))
	{
		if (tkn->type & (VAR | WORD) || (tkn->type & WHITE_SPC && tkn->stat & (IN_DQUOTE | IN_QUOTE)))
		{
			if (!flag && (tkn->stat & (IN_DQUOTE | IN_QUOTE) && cnt++))
				flag = 1;
			else if(flag && !(tkn->stat & (IN_DQUOTE | IN_QUOTE)))
      				flag = 0;
			else if (!(flag && (tkn->stat & (IN_DQUOTE | IN_QUOTE))))
				cnt++;
		}
		tkn = tkn->next;
	}
	return (cnt);
}

char	**get_arg(t_tkns *tkn, int *error)
{
	char	**arg;
	char	*str;
	int	delim;
	int	len;
	int	i;
	int	cnt;

	delim = PIPE | AND | OR | HERE_DOC | APPEND | REDR_O | REDR_I;
	cnt = count_arg(tkn);
	if(!cnt)
		return (NULL);
	arg = ft_calloc(cnt, sizeof(*arg));
	if(!arg)
		return(*error = 1, NULL);
	i = 0;
	while(tkn && !(tkn->type & delim) && i < cnt)
	{
		len = 0;
		if (tkn->type & (VAR | WORD) || (tkn->type & WHITE_SPC && tkn->stat & (IN_DQUOTE | IN_QUOTE)))
		{
			str = tkn->val;
			if(!(tkn->stat & (IN_DQUOTE | IN_QUOTE)))
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
			if(!arg[i])
				return(*error = 1, arg);
			i++;
		}
		if (tkn)
			tkn = tkn->next;
	}
	return (arg);
}

