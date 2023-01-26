/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:16:18 by alemsafi          #+#    #+#             */
/*   Updated: 2023/01/26 14:40:17 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/libft.h"
#include "../include/parser.h"

int	no_delims(t_tkns *tkns, int delim)
{
	while (tkns)
	{
		if (tkns->type & delim)
			return (0);
		tkns = tkns->next;
	}
	return (1);
}

t_tree	*giv_tree(t_tkns *tkns)
{
	t_tkns	*tmp;
	t_tree	*treenode;

	tmp = tkns;
	treenode = logops(tkns);
	return (treenode);
}

t_tree	*logops(t_tkns *tkns)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		subsh;

	if (no_delims(tkns, AND | OR))
		return (pipe(tkns));
	treenode = malloc(sizeof(t_tree));
	tmp = tkns;
	subsh = tmp->sbsh;
	while (tmp && !(subsh && !tmp->sbsh))
	{
		if ((tmp->type & (AND | OR)) && subsh)
		{
			if (!tmp->prev || !tmp->next)
			{
				return (printf("Syntax Error"), NULL);
				freetree(treenode);
			}
			treenode->tkn = tmp;
			treenode->lisr = pipe(tkns);
			treenode->limn = logops(tmp->next);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}

t_tree	*pipe(t_tkns *tkns)
{
	t_tkns	*tmp;
	t_tree	*treenode;
	int		subsh;

	tmp = tkns;
	if (no_delims(tkns, PIPE))
		return (cmdlist(tkns));
	treenode = malloc(sizeof(t_tree));
	subsh = tmp->sbsh;
	while (tmp && !(tmp->type & (AND | OR)) && !(subsh && !tmp->sbsh))
	{
		if (tmp->type & PIPE)
		{
			if (!tmp->prev || !tmp->next)
				return (printf("Syntax Error"), NULL);
			treenode->tkn = tmp;
			treenode->lisr = cmdlist(tkns);
			treenode->limn = pipe(tmp->next);
			break ;
		}
		tmp = tmp->next;
	}
	return (treenode);
}
//search for && ||
//the left pointer of the tree node will point at the start of the tkns list
//the right pointer of the tree node will point at the token coming after the the node
//we will pass the left pointer to a function which will look for |
//we will pass the right pointer to the same function (giv_tree) too look for potential	|| &&(recursion)
//create a function for each
