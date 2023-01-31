/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:59:10 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/31 11:33:22 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_tree	*redir(t_tkns *tkn, int *error)
{
	t_tree	*redr;
	t_tree	*file;

	redr = ft_calloc(1, sizeof(*redr));
	if (!redr)
		return (*error = 1, redr);
	redr->tkn = tkn;
	tkn = tkn->next;
	while (tkn)
	{
		if (tkn->type & (WORD | VAR))
			break ;
		else if (tkn->type & WHITE_SPC)
			tkn = tkn->next;
		else
			return (*error = 2, redr);
	}
	if (!tkn)
		return (*error = 2, redr);
	file = ft_calloc(1, sizeof(*file));
	if (!file)
		return (*error = 1, redr);
	file->tkn = tkn;
	redr->limn = file;
	return (redr);
}

t_tree	*cmdlst(t_tkns *tkn, int *error)
{
	t_tree	*cmdlst;
	t_tkns	*tmp;
	int	type;

	tmp = NULL;
	type = HERE_DOC | APPEND | REDR_O | REDR_I;
	if (tkn->type & OPAR && tkn->next->sbsh & IN_PAR)
	{
		tkn = tkn->next;
		cmdlst = giv_tree(tkn, error);
		while (tkn && (tkn->sbsh & IN_PAR))
			tkn = tkn->next;
		while (tkn && (tkn->type & WHITE_SPC || tkn->type & CPAR))
			tkn = tkn->next;
		if (tkn && (tkn->type & type))
		{
			cmdlst->redr = redir(tkn, error);
			if (*error)
				return (cmdlst);
			tmp = cmdlst->redr->limn->tkn->next;
			while (tmp && (tmp->type & WHITE_SPC))
				tmp = tmp->next;
			if (!(tmp->type & (PIPE | AND | OR)))
				return (*error = 2, cmdlst);
		}
		else if (tkn && !(tkn->type & (PIPE | AND | OR)))
			return (*error = 2, cmdlst);
	}
	else
	{
		cmdlst = cmd(tkn, error);
		if (*error)
			return (cmdlst);
		if (cmdlst->redr)
			tmp = cmdlst->redr->limn->tkn->next;
		else
			tmp = tkn->next;
		while (tmp && tmp->type & WHITE_SPC)
			tmp = tmp->next;
		if (tmp && (tmp->type & OPAR && !tmp->stat))
			return (*error = 2, cmdlst);
	}
	return (cmdlst);
}

t_tree	*cmd(t_tkns *tkn, int *error)
{
	t_tkns	*tmp;
	t_tree	*cmd;
	t_tree	*redr;
	int	type;

	type = HERE_DOC | APPEND | REDR_O | REDR_I;
	cmd = NULL;
	tmp = tkn;
	if (!(tkn->type & type))
	{
		cmd = ft_calloc(1, sizeof(*cmd));
		if (!cmd)
			return (*error = 1, cmd);
		cmd->tkn = tkn;
		cmd->arg = get_arg(tkn->next, error);
		if (*error)
			return (cmd);
	}
	while (tmp && !(tmp->type & type) &&
			!(tmp->type & (PIPE | AND | OR)) && (tmp->type & WHITE_SPC))
		tmp = tmp->next;
	if (tmp && (tmp->type & type))
	{
		redr = redir(tmp, error);
		if (*error)
			return (free(cmd), redr);
		if (cmd)
			return (cmd->redr = redr, cmd);
		else
			return (redr);
	}
	return (cmd);
}

