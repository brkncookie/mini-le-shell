/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:23:15 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/27 10:27:07 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include <stdlib.h>

typedef struct s_tree
{
	t_tkns	*tkn;
	t_tree	*limn;
	t_tree	*lisr;
	t_tree	*redr;
}		t_tree;

t_tree	*giv_tree(t_tkns *tkns);
t_tree	*logops(t_tkns *tkns, int *error);
t_tree	*pipe(t_tkns *tkns, int *error);
int		no_delims(t_tkns *tkns, int delim);
t_tree	*cmdlst(t_tkns *tkn, int *error);
t_tree	*redir(t_tkns *tkn, int *error);
t_tree	*cmd(t_tkns *tkn, int *error);

#endif

