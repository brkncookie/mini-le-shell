/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:16:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/01/28 17:40:27 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	no_delims(t_tkns *tkns, int delim)
{
	int	subsh;

	subsh = tkns->sbsh;
	while (tkns)
	{
		if (tkns->type & delim)
		{
			if(!subsh && tkns->sbsh)
			{
				tkns = tkns->next;
				continue;
			}
			return (0);
		}
		tkns = tkns->next;
	}
	return (1);
}

t_tree	*giv_tree(t_tkns *tkns)
{
	t_tree	*treenode;
	int	error;

	error = 0;
	while (tkns->type & WHITE_SPC)
		tkns = tkns->next;
	treenode = logops(tkns, &error);
	if (error)
	{
		if (error == 2)
			printf("Syntax Error\n");
		else if (error == 1)
			printf("Allocation Error\n");
		return(freetree(treenode), freelst(&tkns), NULL);
	}
	return (treenode);
}

t_tree	*logops(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		subsh;

	if (no_delims(tkns, AND | OR))
		return (lqados(tkns, error));
	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	tmp = tkns;
	subsh = tmp->sbsh;
	while (tmp && !(subsh && !tmp->sbsh))
	{
		if (!subsh && tmp->sbsh)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type & (AND | OR))
		{
			if (!tmp->prev || !tmp->next)
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = lqados(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next->type & WHITE_SPC)
				tmp = tmp->next;
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
	int		subsh;

	tmp = tkns;
	if (no_delims(tkns, PIPE))
		return (cmdlst(tkns, error));
	treenode = ft_calloc(1, sizeof(t_tree));
	if (!treenode)
		return (*error = 1, treenode);
	subsh = tmp->sbsh;
	while (tmp && !(tmp->type & (AND | OR)) && !(subsh && !tmp->sbsh))
	{
		if (!subsh && tmp->sbsh)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type & PIPE)
		{
			if (!tmp->prev || !tmp->next)
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = cmdlst(tkns, error);
			if (*error)
				return (treenode);
			while (tmp->next->type & WHITE_SPC)
				tmp = tmp->next;
			treenode->limn = lqados(tmp->next, error);
			if (*error)
				return (treenode);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}
