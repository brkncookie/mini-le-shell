/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:16:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/02/12 10:30:21 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	skip_pars(t_tkns **tkns)
{
	while (*tkns && !((*tkns)->type & CPAR))
	{
		*tkns = (*tkns)->next;
		if ((*tkns) && (*tkns)->type & OPAR)
			skip_pars(tkns);
	}
	if ((*tkns) && (*tkns)->type & CPAR)
		*tkns = (*tkns)->next;
	return (1);
}

t_tree	*giv_tree(t_tkns *tkns, int *error)
{
	t_tree	*treenode;

	treenode = logops(tkns, error);
	if (*error)
	{
		if (*error == 2)
			printf("Syntax Error\n");
		else if (*error == 1)
			printf("Allocation Error\n");
		return (freetree(treenode), freelst(&tkns), NULL);
	}
	return (treenode);
}

t_tree	*logops(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;

	treenode = NULL;
	while (tkns && tkns->type & WHITE_SPC)
		tkns = tkns->next;
	if (no_delims(tkns, AND | OR, 0))
		return (lqados(tkns, error));
	tmp = tkns;
	while (tmp && (!(tmp->type & CPAR) || (tmp->type & CPAR && tmp->stat)))
	{
		if (tmp && tmp->type & OPAR && skip_pars(&tmp))
			continue ;
		if (tmp->type & (AND | OR))
		{
			treenode = node_create(&tmp, tkns, error, lqados, logops);
			if (*error)
				return (treenode);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}

t_tree	*lqados(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;

	treenode = NULL;
	tmp = tkns;
	if (no_delims(tkns, PIPE, AND | OR))
		return (cmdlst(tkns, error));
	while (tmp && (!(tmp->type & (CPAR | AND | OR))
			|| (tmp->type & (CPAR | AND | OR) && tmp->stat)))
	{
		if (tmp && tmp->type & OPAR && skip_pars(&tmp))
			continue ;
		if (tmp->type & PIPE)
		{
			treenode = node_create(&tmp, tkns, error, cmdlst, lqados);
			if (*error)
				return (treenode);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}

t_tree	*node_create(t_tkns **tmp, t_tkns *tkns, int *error,
		t_tree *(*lyasar)(t_tkns *, int *), t_tree *(*lyamin)(t_tkns *, int *))
{
	t_tree	*treenode;

	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	treenode->tkn = (*tmp);
	treenode->lisr = lyasar(tkns, error);
	while ((*tmp)->next && ((*tmp)->next->type & WHITE_SPC
			|| ((*tmp)->next->type & CPAR)))
		(*tmp) = (*tmp)->next;
	if (!(*tmp)->next || (tkns->type & PIPE))
		return (*error = 2, treenode);
	treenode->limn = lyamin((*tmp)->next, error);
	return (treenode);
}
