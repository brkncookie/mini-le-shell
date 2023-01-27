/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:16:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/01/27 10:51:10 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	no_delims(t_tkns *tkns, int delim)
{
	while (tkns)
	{
		if (!tkns->sbsh && (tkns->type & delim))
			return (0);
		tkns = tkns->next;
	}
	return (1);
}

t_tree	*giv_tree(t_tkns *tkns)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		error;

	tmp = tkns;
	error = 0;
	treenode = logops(tkns, &error);
	if (error)
	{
		if (error == 2)
			printf("Syntax Error\n");
		else if (error == 1)
			printf("Allocation Error\n");
		freetree(treenode);
	}
	return (treenode);
}

t_tree	*logops(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		subsh;

	if (no_delims(tkns, AND | OR))
		return (pipe(tkns, error));
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
		if ((tmp->type & (AND | OR)) && subsh)
		{
			if (!tmp->prev || !tmp->next)
				return (*error = 2, treenode);
			treenode->tkn = tmp;
			treenode->lisr = pipe(tkns, error);
			while (tmp->next->type & WHITE_SPC)
				tmp = tmp->next;
			treenode->limn = logops(tmp->next, error);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}

t_tree	*pipe(t_tkns *tkns, int *error)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		subsh;

	tmp = tkns;
	if (no_delims(tkns, PIPE))
		return (cmdlist(tkns, error));
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
			treenode->lisr = cmdlist(tkns, error);
			while (tmp->next->type & WHITE_SPC)
				tmp = tmp->next;
			treenode->limn = pipe(tmp->next, error);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}

void	freetree(t_tree *tree)
{
	if (!tree)
		return ;
	freetree(tree->limn);
	freetree(tree->lisr);
	free(tree);
}