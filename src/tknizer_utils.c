/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:49:16 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/07 11:50:56 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <stdio.h>

int	is_blncd(char **str, char c)
{
	char	tmp;

	while (c && (*str)++ && **str && **str != c)
		if ((**str == '(' && c == ')') || (**str == '\'' && c == ')') || (**str == '\"'&& c == ')'))
			if (!(is_blncd(str, (**str == '(') + **str)))
				break ;
	if (c)
		return (!(**str == 0));
	while (**str)
	{
		tmp = **str;
		if (tmp == '\'' || tmp == '\"' || tmp == '(')
		{
			if (!(is_blncd(str, (tmp == '(') + tmp)))
				return (0);
		}
		else if (tmp == ')')
			return (0);
		(*str)++;
	}
	return (1);
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

int	glen(char *str, t_tkns *tkn, int *opn)
{
	int	len;
	int	twochar;
	int	sopn;

	len = 0;
	sopn = *opn;
	twochar = APPEND | HERE_DOC | OR | AND;
	if (tkn->type & twochar && !gstat(tkn->type, opn, NULL))
		return (2);
	while (*str)
	{
		if ((*str == '|' || *str == '<' || *str == '>' || \
		(*str == '&' && *(str + 1) == '&') || *str == '(' || *str == ')' || \
		*str == '\"' || *str == '\'' || ft_isspace(*str)) && !gstat(id_type(str), opn, NULL))
		{
			gstat(id_type(str), opn, NULL);
			break;
		}
		else if (str++)
			len++;
	}
	if (!(tkn->type & WORD) && sopn)
		tkn->type = WORD;
	return (len);
}


t_tkns	*tkn_create(char **str, t_type type, t_tkns *tkn)
{
	static int	opn = 0;
	static int	par = 0;
	int			i;
	int		mchar;
	int		schar;

	mchar = WORD | VAR | APPEND | HERE_DOC | OR | AND;
	schar = PIPE | REDR_O | WHITE_SPC | REDR_I | QUOTE | DQUOTE | OPAR | CPAR;
	tkn = ft_calloc(1, sizeof(*tkn));
	i = 0;
	if (!tkn)
		return (NULL);
	tkn->val = *str;
	tkn->type = type;
	tkn->stat = gstat(type, &opn, NULL);
	tkn->sbsh = gstat(type, NULL, &par);
	if (type & mchar || ((type & schar) && tkn->stat))
		tkn->len = glen(*str, tkn, &opn);
	else if (type & schar)
		tkn->len = 1;
	while (i + 1 < tkn->len)
		if (tkn->val[i++] == ';' && tkn->val[i] == ';' && !tkn->stat)
			return (printf("Syntax Error\n"), exit(0), NULL);
	return (*str += tkn->len, tkn);
}

void	tkn_link(t_tkns **lst, t_tkns *tkn)
{
	t_tkns	*tmp;

	tkn->next = NULL;
	tkn->prev = NULL;
	tmp = *lst;
	if (tkn == NULL)
	{
		freelst(lst);
		return ;
	}
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
