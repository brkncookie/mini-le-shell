/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:19:08 by alemsafi          #+#    #+#             */
/*   Updated: 2023/02/15 16:02:33 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/libft.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	if (tree->redr)
	{
		printf(" ");
		while (i < tree->redr->tkn->len)
			printf("%c", tree->redr->tkn->val[i++]);
		i = 0;
		printf(" ");
		while (i < tree->redr->limn->tkn->len)
			printf("%c", tree->redr->limn->tkn->val[i++]);
	}
	i = 1;
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
	}
	printf("\n");
	print_tree(tree->lisr, spaces);
}

/* int	main(int argc, char **argv) */
/* { */
/*  	t_tkns	*tkns; */
/*  	int		i; */

/*  	(void)argc; */
/*  	tkns = tokenize(argv[1]); */
/*  	while (tkns) */
/*  	{ */
/*  		i = 0; */
/*  		while (i < tkns->len) */
/*  			printf("%c", tkns->val[i++]); */
/*  		printf("\n%d\n%d\n%d", tkns->type, tkns->stat, tkns->sbsh); */
/*  		printf("\n----NEXT TOKEN----\n"); */
/*  		tkns = tkns->next; */
/*  	} */
/*  	return (0); */
/* } */

int	main(void)
{
	t_tkns	*tkns;
	t_tree	*tree;
	int		error;
	char	*cmd_buf;

	while (1)
	{
		error = 0;
		cmd_buf = readline("Mini-le-Shell> ");
		if (!(ft_strncmp(cmd_buf, "exit", 4)))
			break ;
		if (ft_strlen(cmd_buf) > 0)
			add_history(cmd_buf);
		tkns = tokenize(cmd_buf);
		if (!tkns)
			continue ;
		tree = giv_tree(tkns, &error);
		print_tree(tree, 0);
	}
	return (0);
}
