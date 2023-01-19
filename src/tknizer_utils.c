/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:49:16 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/19 12:48:29 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../include/lexer.h"

void	*ft_calloc(int nmem, size_t smem);

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

int	glen(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '|' && *str != '<' && *str != '>' && *str != '&' \
			&& *str != '(' && *str != ')' && !ft_isspace(*str))
	{
		str++;
		len++;
	}
	return (len);
}

int	gstat(t_type type, int opn)
{
	if ((type & QUOTE) && !opn)
		opn = 1;
	else if ((type & QUOTE) && opn == 1)
		opn = 0;
	if ((type & DQUOTE) && !opn)
		opn = 2;
	else if ((type & DQUOTE) && opn == 2)
		opn = 0;
	if (opn == 1 && !(type & QUOTE))
		return (IN_QUOTE);
	else if (opn == 2 && !(type & DQUOTE))
		return (IN_DQUOTE);
	return (0);
}

struct s_tkns	*tkn_create(char *str, t_type type)
{
	t_tkns			*tkn;
	int				mchar;
	int				schar;
	static int		opn = 0;

	mchar = WORD | VAR | APPEND | HERE_DOC | OR | AND;
	schar = PIPE | REDR_O | WHITE_SPC | REDR_I | QUOTE | DQUOTE | OPAR | CPAR;
	tkn = ft_calloc(1, sizeof(*tkn));
	if (!tkn)
		return (NULL);
	if (type & schar)
	{
		tkn->val = str;
		tkn->len = 1;
		tkn->type = type;
		tkn->stat = gstat(type, opn);
	}
	else if (type & mchar)
	{
		tkn->val = str;
		tkn->len = glen(str);
		tkn->type = type;
		tkn->stat = gstat(type, opn);
	}
	return (tkn);
}

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%d\n", is_blncd(argv[1], 0));
	return (0);
}
