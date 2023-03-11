/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:59:10 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/11 12:06:17 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_tree	*get_redr(t_tkns *tkn, int type, int *error, t_tree *cmd)
{
	t_tree	*redr;

	while (tkn && !(tkn->type & type) && \
			!(tkn->type & (PIPE | AND | OR | CPAR)))
		tkn = tkn->next;
	if (tkn && (tkn->type & type))
	{
		redr = redir(tkn, error);
		if (*error)
			return (free(cmd), redr);
		if (cmd)
			return (cmd->redr = redr, cmd);
		else
			return (redr);
	}
	return (cmd);
}

t_tree	*redir(t_tkns *tkn, int *error)
{
	t_tree	*redr;

	redr = ft_calloc(1, sizeof(*redr));
	if (!redr)
		return (*error = 1, redr);
	redr->tkn = tkn;
	tkn = tkn->next;
	while (tkn)
	{
		if (tkn->type & WHITE_SPC)
			tkn = tkn->next;
		else if (tkn->type & (WORD | VAR) || !(tkn->type & (WORD | VAR))) //wtf is this condition bhalla ktbi else if(1)
			break ;
	}
	if (!tkn || !(tkn->type & (WORD | VAR)))
		return (*error = 2, redr);
	redr->limn = ft_calloc(1, sizeof(*redr));
	if (!redr->limn)
		return (*error = 1, redr);
	redr->limn->tkn = tkn;
	redr->redr = get_redr(tkn, (HERE_DOC | APPEND | REDR_O | REDR_I), \
			error, NULL);
	return (redr);
}

t_tree	*get_subsh(t_tkns *tkn, int type, int *error)
{
	t_tree	*cmdlst;
	t_tkns	*tmp;

	tmp = NULL;
	cmdlst = logops(tkn->next, error);
	skip_pars(&tkn);
	while (tkn && (tkn->type & WHITE_SPC))
		tkn = tkn->next;
	if (tkn && (tkn->type & type))
	{
		cmdlst->redr = redir(tkn, error);
		if (*error)
			return (cmdlst);
		tmp = cmdlst->redr->limn->tkn->next;
		while (tmp && (tmp->type & WHITE_SPC))
			tmp = tmp->next;
		if (tmp && !(tmp->type & (PIPE | AND | OR | CPAR | type)))
			return (*error = 2, cmdlst);
	}
	else if (tkn && !(tkn->type & (PIPE | AND | OR | CPAR | type)))
		return (*error = 2, cmdlst);
	return (cmdlst);
}

t_tree	*cmdlst(t_tkns *tkn, int *error)
{
	t_tree	*cmdlst;
	t_tkns	*tmp;
	int		type;

	tmp = NULL;
	type = HERE_DOC | APPEND | REDR_O | REDR_I;
	if (tkn->type & OPAR && !(tkn->stat))
		return (get_subsh(tkn, type, error));
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
	t_tree	*cmd;
	int		type;

	type = HERE_DOC | APPEND | REDR_O | REDR_I;
	cmd = NULL;
	while (tkn && (tkn->type & (DQUOTE | QUOTE) || tkn->type & WHITE_SPC))
		tkn = tkn->next;
	if (!(tkn->type & type))
	{
		cmd = ft_calloc(1, sizeof(*cmd));
		if (!cmd)
			return (*error = 1, cmd);
		cmd->arg = get_arg(cmd->tkn = tkn, error);
		if (*error)
			return (cmd);
	}
	return (get_redr(tkn, type, error, cmd));
}
