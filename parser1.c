/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:59:10 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/23 13:48:36 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

/* t_tree	*cmdlst(t_tkns *tkn) */
/* { */
/* } */

t_tree	*redir(t_tkns *tkn)
{
	int		first;
	t_tree	*redr;
	t_tree	*file;
	int		spc;

	spc = AND | OR | PIPE | HERE_DOC | REDR_I | REDR_O | APPEND;
	if (!tkn->prev)
		first = 1;
	redr = ft_calloc(1, sizeof(*redr));
	redr->tkn = tkn;
	while (tkn)
	{
		if (tkn->type & (WORD | VAR))
			break ;
		else if (tkn->type & WHITE_SPC)
			tkn = tkn->next;
		else
			return (free(redr), NULL);
	}
	file = ft_calloc(1, sizeof(*file));
	file->tkn = tkn;
	redr->limn = file;
	if (!first && tkn->next)
	{
		tkn = tkn->next;
		while (tkn->type & WHITE_SPC)
			tkn = tkn->next;
		if (!(tkn->type & spc))
			return (free(redr), free(file), NULL);
	}
	return (redr);
}
