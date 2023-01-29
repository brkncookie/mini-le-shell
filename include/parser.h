/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saltysushi <saltysushi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:23:15 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/28 15:49:41 by saltysushi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "stdio.h"
# include <stdlib.h>

typedef struct s_tree
{
	t_tkns	*tkn;
	struct s_tree	*limn;
	struct s_tree	*lisr;
	struct s_tree	*redr;
	char		**arg;
}		t_tree;

t_tree	*giv_tree(t_tkns *tkns);
t_tree	*logops(t_tkns *tkns, int *error);
t_tree	*lqados(t_tkns *tkns, int *error);
int	no_delims(t_tkns *tkns, int delim, int stop);
t_tree	*cmdlst(t_tkns *tkn, int *error);
t_tree	*redir(t_tkns *tkn, int *error);
t_tree	*cmd(t_tkns *tkn, int *error);
void	freetree(t_tree *tree);
char	**get_arg(t_tkns *tkn, int *error);

#endif

