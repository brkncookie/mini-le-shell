#include "../include/lexer.h"
#include "../include/libft.h"
#include "../include/parser.h"

void	print_tree(t_tree *tree, int spaces)
{
	int	i;

	if (!tree || !tree->tkn)
		return ;
	spaces += 10;
	print_tree(tree->limn, spaces);
	i = 0;
	while (i < spaces)
	{
		printf(" ");
		i++;
	}
	i = 0;
	while (i < tree->tkn->len)
		printf("%c", tree->tkn->val[i++]);
	printf("\n");
	print_tree(tree->lisr, spaces);
}

int main(int ac, char **av)
{
	t_tkns	*tkns;
	t_tree	*tree;

	tkns = tokenize(av[1]);
	tree = giv_tree(tkns);
	print_tree(tree, 0);
	return (0);
}

