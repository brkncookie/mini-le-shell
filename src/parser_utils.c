/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:07:57 by alemsafi          #+#    #+#             */
/*   Updated: 2023/04/05 02:28:02 by alemsafi         ###   ########.fr       */
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
		if ((*lst)->val && !((*lst)->len))
			free((*lst)->val);
		free(*lst);
		(*lst) = tmp;
	}
}

int	count_arg(t_tkns *tkn)
{
	int	cnt;
	int	delim;

	delim = PIPE | AND | OR | HERE_DOC | APPEND | REDR_O | REDR_I;
	cnt = 0;
	while (tkn && !(tkn->type & delim))
	{
		if (tkn->type & (VAR | WORD))
			cnt++;
		tkn = tkn->next;
	}
	return (cnt);
}

int	make_arg(t_tkns **tkn, char **ar, int i, int *error)
{
	ar[i] = ft_strndup((*tkn)->val, (*tkn)->len);
	if (!ar[i])
		return (*error = 1, 0);
	while ((*tkn) && !((*tkn)->type & WHITE_SPC) && (*tkn)->next
		&& (*tkn)->next->type & (QUOTE | DQUOTE))
	{
		(*tkn) = (*tkn)->next->next;
		while ((*tkn) && ((*tkn)->stat & (IN_QUOTE | IN_DQUOTE)
				|| (*tkn)->type & (VAR | WORD | QUOTE | DQUOTE)))
		{
			if (!((*tkn)->type & (QUOTE | DQUOTE)))
				(void)((ar[i] = ft_realloc(ar[i], ft_strlen(ar[i]) + (*tkn)->len
								+ 1)) + ft_strlcat(ar[i], (*tkn)->val,
							(*tkn)->len + ft_strlen(ar[i]) + 1));
			(*tkn) = (*tkn)->next;
		}
	}
	while ((*tkn) && !((*tkn)->type & WHITE_SPC) && (*tkn)->next
		&& (*tkn)->next->type & (VAR | WORD))
	{
		(*tkn) = (*tkn)->next;
		ar[i] = ft_realloc(ar[i], ft_strlen(ar[i]) + (*tkn)->len + 1);
		ft_strlcat(ar[i], (*tkn)->val, (*tkn)->len + ft_strlen(ar[i]) + 1);
	}
	return (1);
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
	arg = ft_calloc(cnt + 2, sizeof(*arg));
	if (!arg)
		return (*error = 1, NULL);
	i = 0;
	while (tkn && !(tkn->type & delim) && i < cnt + 1)
	{
		if (tkn->type & (VAR | WORD))
		{
			if (!make_arg(&tkn, arg, i, error))
				return (fre2d(arg), freelst(&tkn), NULL);
			i++;
		}
		if (tkn)
			tkn = tkn->next;
	}
	return (arg[i] = NULL, arg);
}

int	no_delims(t_tkns *tkns, int delim, int stop)
{
	while (tkns && (!(tkns->type & CPAR) || (tkns->type & CPAR && tkns->stat)))
	{
		if (tkns && tkns->type & OPAR)
		{
			skip_pars(&tkns);
			continue ;
		}
		if (tkns && tkns->type & stop)
			return (1);
		if (tkns && tkns->type & delim && !tkns->stat)
			return (0);
		if (tkns)
			tkns = tkns->next;
	}
	return (1);
}
