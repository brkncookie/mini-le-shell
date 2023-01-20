/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:49:16 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/20 10:05:40 by mnadir           ###   ########.fr       */
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

int	glen(char *str, t_type type)
{
	int	len;
	int	twochar;

	len = 0;
	twochar = APPEND | HERE_DOC | OR | AND;
	if (type & twochar)
		return (2);
	while (*str && *str != '|' && *str != '<' && *str != '>' && *str != '&'
		&& *str != '(' && *str != ')' && \
		*str != '\"' && *str != '\'' && !ft_isspace(*str))
	{
		str++;
		len++;
	}
	return (len);
}

int	gstat(t_type type, int *opn, int *par)
{
	if (par && (type & OPAR) && !*par)
		*par = 1;
	else if (par && (type & CPAR) && *par == 1)
		*par = 0;
	if (par && *par == 1 && !(type & OPAR) && !(type & CPAR))
		return (IN_PAR);
	if (!opn)
		return (0);
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
	static int	par = 0;

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
		tkn->stat = gstat(type, &opn, NULL);
		tkn->sbsh = gstat(type, NULL, &par);
	}
	else if (type & mchar)
	{
		tkn->val = *str;
		tkn->len = glen(*str, type);
		tkn->type = type;
		tkn->stat = gstat(type, &opn, NULL);
		tkn->sbsh = gstat(type, NULL, &par);
	}
	return (*str += tkn->len, tkn);
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

