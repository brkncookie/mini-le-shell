#include "../include/lexer.h"
#include "../include/libft.h"
#include "../include/parser.h"

void	print_tree(t_tree *tree, int spaces)
{
	int	i;
	int	j;

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
	i = 0;
	if (!tree->limn && !tree->lisr)
	{
		while (tree->arg && tree->arg[i])
		{
			j = 0;
			printf(" ");
			while (tree->arg[i][j])
				printf("%c", tree->arg[i][j++]);
			i++;
		}
		i = 0;
		if(tree->redr)
		{
			printf(" ");
			while (i < tree->redr->tkn->len)
				printf("%c", tree->redr->tkn->val[i++]);
			i = 0;
			printf(" ");
			while (i < tree->redr->limn->tkn->len)
				printf("%c", tree->redr->limn->tkn->val[i++]);
		}
	}
	printf("\n");
	print_tree(tree->lisr, spaces);
}

int main(int ac, char **av)
{
	t_tkns	*tkns;
	t_tree	*tree;
	int	error;
	(void)ac;

	error = 0;
	tkns = tokenize(av[1]);
	if (!tkns)
		return (0);
	tree = giv_tree(tkns, &error);
	print_tree(tree, 0);
	return (0);
}

