/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:23:15 by mnadir            #+#    #+#             */
/*   Updated: 2023/04/04 15:11:22 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include <stdio.h>

typedef struct s_tree
{
	t_tkns			*tkn;
	struct s_tree	*limn;
	struct s_tree	*lisr;
	struct s_tree	*redr;
	char			**arg;
}					t_tree;

t_tree		*giv_tree(t_tkns *tkns, int *error);
t_tree		*logops(t_tkns *tkns, int *error);
t_tree		*lqados(t_tkns *tkns, int *error);
int			no_delims(t_tkns *tkns, int delim, int stop);
t_tree		*cmdlst(t_tkns *tkn, int *error);
t_tree		*redir(t_tkns *tkn, int *error);
t_tree		*cmd(t_tkns *tkn, int *error);
void		freetree(t_tree *tree);
char		**get_arg(t_tkns *tkn, int *error);
void		fre2d(char **path);
int			skip_pars(t_tkns **tkns);
char		*ft_realloc(char *str, int len);
t_tree		*node_create(t_tkns **tmp, t_tkns *tkns, int *error,
				t_tree *(*lyasar)(t_tkns *, int *),
				t_tree *(*lyamin)(t_tkns *, int *));
void		fre2d(char **path);
#endif
