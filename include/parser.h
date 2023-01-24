#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

typedef struct s_tree
{
	t_tkns	*tkn;
	t_tree	*limn;
	t_tree	*lisr;
} t_tree;
#endif

