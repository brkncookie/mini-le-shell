/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:16:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/02/05 16:07:34 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	skip_pars(t_tkns **tkns)
{
	while (*tkns && !((*tkns)->type & CPAR))
	{
		*tkns = (*tkns)->next;
		if ((*tkns) && (*tkns)->type & OPAR)
			skip_pars(tkns);
	}
	if ((*tkns) && (*tkns)->type & CPAR)
		*tkns = (*tkns)->next;
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

	while (tkns && tkns->type & WHITE_SPC)
		tkns = tkns->next;
	if (no_delims(tkns, AND | OR, 0))
		return (lqados(tkns, error));
	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	tmp = tkns;
	while (tmp && (!(tmp->type & CPAR) || (tmp->type & CPAR && tmp->stat)))
	{
		if (tmp && tmp->type & OPAR)
		{
			skip_pars(&tmp);
			continue ;
		}
		if (tmp->type & (AND | OR))
		{
			if (!tmp->prev || !tmp->next || (tkns->type & (AND | OR)))
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = lqados(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next && (tmp->next->type & WHITE_SPC
					|| (tmp->next->type & CPAR)))
				tmp = tmp->next;
			if (!tmp->next)
				return (*error = 2, treenode);
			treenode->limn = logops(tmp->next, error);
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

	tmp = tkns;
	if (no_delims(tkns, PIPE, AND | OR))
		return (cmdlst(tkns, error));
	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	while (tmp && (!(tmp->type & (CPAR | AND | OR))
			|| (tmp->type & (CPAR | AND | OR) && tmp->stat)))
	{
		if (tmp && tmp->type & OPAR)
		{
			skip_pars(&tmp);
			continue ;
		}
		if (tmp->type & PIPE)
		{
			if (!tmp->prev || !tmp->next || (tkns->type & PIPE))
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = cmdlst(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next && (tmp->next->type & WHITE_SPC
					|| (tmp->next->type & CPAR)))
				tmp = tmp->next;
			if (!tmp->next)
				return (*error = 2, treenode);
			treenode->limn = lqados(tmp->next, error);
			if (*error)
				return (treenode);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}
