/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:49:16 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/20 09:26:10 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/libft.h"
#include <stdio.h>

int	is_blncd(char *str, char c)
{
	char	tmp;

	if (c)
		while (*str && *str != c)
			str++;
	if (c)
		return (!(*str == 0));
	while (*str)
	{
		tmp = *str;
		if (tmp == '\'' || tmp == '\"' || tmp == '(')
		{
			if (tmp == '(')
				tmp = ')';
			if (is_blncd(str + 1, tmp) && str++)
				while (*str && *str != tmp)
					str++;
			else
				return (0);
		}
		else if (tmp == ')')
			return (0);
		str++;
	}
	return (1);
}

int	ft_isspace(char c)
{
	if (c == '\n' || c == '\r' || c == '\f' || c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	glen(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '|' && *str != '<' && *str != '>' && *str != '&'
		&& *str != '(' && *str != ')' && *str != '\"' && *str != '\'' && !ft_isspace(*str))
	{
		str++;
		len++;
	}
	return (len);
}

int	gstat(t_type type, int *opn)
{
	if ((type & QUOTE) && !*opn)
		*opn = 1;
	else if ((type & QUOTE) && *opn == 1)
		*opn = 0;
	if ((type & DQUOTE) && !*opn)
		*opn = 2;
	else if ((type & DQUOTE) && *opn == 2)
		*opn = 0;
	if (*opn == 1 && !(type & QUOTE))
		return (IN_QUOTE);
	else if (*opn == 2 && !(type & DQUOTE))
		return (IN_DQUOTE);
	return (0);
}

t_tkns	*tkn_create(char **str, t_type type)
{
	t_tkns		*tkn;
	int			mchar;
	int			schar;
	static int	opn = 0;

	mchar = WORD | VAR | APPEND | HERE_DOC | OR | AND;
	schar = PIPE | REDR_O | WHITE_SPC | REDR_I | QUOTE | DQUOTE | OPAR | CPAR;
	tkn = ft_calloc(1, sizeof(*tkn));
	if (!tkn)
		return (NULL);
	if (type & schar)
	{
		tkn->val = *str;
		tkn->len = 1;
		tkn->type = type;
		tkn->stat = gstat(type, &opn);
	}
	else if (type & mchar)
	{
		tkn->val = *str;
		tkn->len = glen(*str);
		tkn->type = type;
		tkn->stat = gstat(type, &opn);
	}
	return (*str += tkn->len, tkn);
}

t_tkns	*tokenize(char *cmds)
{
	t_tkns	*tkns;

	// if (!is_blncd(cmds, 0))
	// 	error;
	tkns = NULL;
	while (*cmds)
	{
		if (*cmds == ' ')
			tkn_link(&tkns, tkn_create(&cmds, WHITE_SPC));
		else if (*cmds == '\'')
			tkn_link(&tkns, tkn_create(&cmds, QUOTE));
		else if (*cmds == '\"')
			tkn_link(&tkns, tkn_create(&cmds, DQUOTE));
		else if (*cmds == '$')
			tkn_link(&tkns, tkn_create(&cmds, VAR));
		else if (*cmds == '(')
			tkn_link(&tkns, tkn_create(&cmds, OPAR));
		else if (*cmds == ')')
			tkn_link(&tkns, tkn_create(&cmds, CPAR));
		else if (*cmds == '|' && *(cmds + 1) == '|')
			tkn_link(&tkns, tkn_create(&cmds, OR));
		else if (*cmds == '|')
			tkn_link(&tkns, tkn_create(&cmds, PIPE));
		else if (*cmds == '&' && *(cmds + 1) == '&')
			tkn_link(&tkns, tkn_create(&cmds, AND));
		else if (*cmds == '>' && *(cmds + 1) == '>')
			tkn_link(&tkns, tkn_create(&cmds, APPEND));
		else if (*cmds == '>')
			tkn_link(&tkns, tkn_create(&cmds, REDR_O));
		else if (*cmds == '<' && *(cmds + 1) == '<')
			tkn_link(&tkns, tkn_create(&cmds, HERE_DOC));
		else if (*cmds == '<')
			tkn_link(&tkns, tkn_create(&cmds, REDR_I));
		else
			tkn_link(&tkns, tkn_create(&cmds, WORD));
	}
	return (tkns);
}

void	tkn_link(t_tkns **lst, t_tkns *tkn)
{
	t_tkns	*tmp;

	tkn->next = NULL;
	tkn->prev = NULL;
	tmp = *lst;
	if (tkn == NULL)
		return ;
	if (!*lst)
	{
		*lst = tkn;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tkn;
	tkn->prev = tmp;
}

int	main(int argc, char **argv)
{
	(void)argc;
	t_tkns	*tkns;
	int		i;

	tkns = tokenize("ana zwin bzaf | \"bruh\"");
	while (tkns)
	{
		i = 0;
		while (i < tkns->len)
			printf("%c", tkns->val[i++]);
		printf("\n%d\n%d", tkns->type, tkns->stat);
		printf("\nnext token\n");
		tkns = tkns->next;
	}
	
	return (0);
}
