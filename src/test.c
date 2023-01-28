#include "../include/lexer.h"
#include "../include/libft.h"
#include "../include/parser.h"

void	print_tree(t_tree *tree)
{
	int	i;

	if (!tree)
		return ;
	i = 0;
	while (i < tree->tkn->len)
	{
		printf("%c", tree->tkn->val[i++]);
	}
	printf("\n ---next token---\n");
	print_tree(tree->limn);
	print_tree(tree->lisr);
}

int main(int ac, char **av)
{
	t_tkns	*tkns;
	t_tree	*tree;

	tkns = tokenize(av[1]);
	tree = giv_tree(tkns);
	print_tree(tree);
	return (0);
}
