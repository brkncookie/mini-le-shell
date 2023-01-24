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

t_tree	*redir(t_tkns *tkn)
{
	t_tree	*redr;
	t_tree	*file;

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
	if(!tkn)
		return (free(redr), NULL);
	file = ft_calloc(1, sizeof(*file));
	file->tkn = tkn;
	redr->limn = file;
	return (redr);
}

t_tree	*cmdlst(t_tkns *tkn)
{
	t_tree	*cmdlst;
	tkns	*tmp;
	int	type;

	type = HERE_DOC | APPEND | REDR_O | REDR_I;
	if (tkn->type & OPAR && tkn->next->sbsh & IN_PAR)
	{
		tkn = tkn->next;
		cmdlst = logops(tkn);
		while(tkn->sbsh & IN_PAR)
			tkn = tkn->next;
		tkn = tkn->next;
		while(tkn->type & WHITE_SPC)
			tkn = tkn->next;
		if (tkn->type & type)
		{
			cmdlst->redr = redir(tkn);
			if (!cmdlst->redr)
			/* here we need to free *cmdlst */
				return (NULL);
			tmp = cmdlst->redr->limn->tkn->next;
			while (tmp && (tmp->type & WHITE_SPC))
				tmp = tmp->next;
			if(!(tmp->type & (PIPE | AND | OR)))
			/* here we need to free *cmdlst */
				return (NULL);
		}
		else (!(tkn->type & (PIPE | AND | OR)))
			/* here we need to free *cmdlst */
			return (NULL);
	}
	else
	{
		cmdlst = cmd(tkn);
		if (!cmdlst)
			return (NULL);
		if (cmdlst->redr)
			tmp = cmdlst->redr->limn->tkn->next;
		while (tmp && (tmp->type & WHITE_SPC))
			tmp = tmp->next;
		if((tmp->sbsh & IN_PAR))
			return (free(cmdlst), NULL);
	}
	return (cmdlst);
}

t_tree	*cmd(t_tkns *tkn)
{
	t_tkns	tmp;
	int	type;
	t_tree  *cmd;
	t_tree  *redr;

	type = HERE_DOC | APPEND | REDR_O | REDR_I;
	cmd = NULL;
	if (!(tkn->type & type))
	{
		cmd = ft_calloc(1, sizeof(*cmd));
		if(!cmd)
			return (NULL);
		cmd->tkn = tkn;
	}
	while (tmp && !(tmp->type & type) &&\
		!(tmp->type & (PIPE | AND | OR) && (tmp->type & WHITE_SPC)
		tmp = tmp->next;
	if (tmp && (tmp->type & type))
	{
		redr = redir(tmp);
		if(!redr)
			return(free(cmd), NULL);
		if(cmd)
			return(cmd->redr = redr, cmd)
		else
			return (redr);
	}
	return (cmd);
}

