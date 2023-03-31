/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:35:44 by mnadir            #+#    #+#             */
/*   Updated: 2023/03/31 14:09:53 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

typedef enum e_type
{
	AND = 1 << 0,
	OR = 1 << 1,
	PIPE = 1 << 2,
	REDR_O = 1 << 3,
	REDR_I = 1 << 4,
	HERE_DOC = 1 << 5,
	APPEND = 1 << 6,
	QUOTE = 1 << 7,
	DQUOTE = 1 << 8,
	OPAR = 1 << 9,
	CPAR = 1 << 10,
	VAR = 1 << 11,
	WORD = 1 << 12,
	WHITE_SPC = 1 << 13
}	t_type;

typedef enum e_stat
{
	IN_QUOTE = 1,
	IN_DQUOTE = 2,
	IN_PAR = 3
}	t_stat;

typedef struct s_tkns
{
	char			*val;
	t_type			type;
	int				len;
	t_stat			stat;
	t_stat			sbsh;
	struct s_tkns	*next;
	struct s_tkns	*prev;
}	t_tkns;

int		tkn_link(t_tkns **lst, t_tkns *tkn);
int		is_blncd(char **str, char c);
t_tkns	*tkn_create(char **str, t_type type, t_tkns *tkn);
void	freelst(t_tkns **lst);
t_tkns	*tokenize(char *cmds, int *error);
int		id_type(char *cmds);

#endif
