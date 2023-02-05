/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:38:31 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/04 13:12:51 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/libft.h"
#include <stdio.h>

int id_type(char *cmds)
{
	if (*cmds == ' ')
		return(WHITE_SPC);
	else if (*cmds == '\'')
		return(QUOTE);
	else if (*cmds == '\"')
		return(DQUOTE);
	else if (*cmds == '$')
		return(VAR);
	else if (*cmds == '(')
		return(OPAR);
	else if (*cmds == ')')
		return(CPAR);
	else if (*cmds == '|' && *(cmds + 1) == '|')
		return(OR);
	else if (*cmds == '|')
		return(PIPE);
	else if (*cmds == '&' && *(cmds + 1) == '&')
		return(AND);
	else if (*cmds == '>' && *(cmds + 1) == '>')
		return(APPEND);
	else if (*cmds == '>')
		return(REDR_O);
	else if (*cmds == '<' && *(cmds + 1) == '<')
		return(HERE_DOC);
	else if (*cmds == '<')
		return(REDR_I);
	return (0);
}
t_tkns	*tokenize(char *cmds)
{
	t_tkns	*tkns;
	char	*str;

	str = cmds;
	if (!is_blncd(&str, 0))
		return (printf("Syntax Error.\n"), NULL);
	tkns = NULL;
	while (*cmds)
	{

		if(*cmds == ' ' || *cmds == '\'' || *cmds == '\"' || *cmds == '$' || \
		*cmds == '(' || *cmds == ')' || (*cmds == '|' && *(cmds + 1) == '|') || \
		*cmds == '|' || (*cmds == '&' && *(cmds + 1) == '&') || (*cmds == '>' && *(cmds + 1) == '>') || \
		*cmds == '>' || (*cmds == '<' && *(cmds + 1) == '<') || *cmds == '<')
			tkn_link(&tkns, tkn_create(&cmds, id_type(cmds), NULL));
		else
			tkn_link(&tkns, tkn_create(&cmds, WORD, NULL));
	}
	return (tkns);
}

 /* int	main(int argc, char **argv) */
 /* { */
 /* 	t_tkns	*tkns; */
 /* 	int		i; */

 /* 	(void)argc; */
 /* 	tkns = tokenize(argv[1]); */
 /* 	while (tkns) */
 /* 	{ */
 /* 		i = 0; */
 /* 		while (i < tkns->len) */
 /* 			printf("%c", tkns->val[i++]); */
 /* 		printf("\n%d\n%d\n%d", tkns->type, tkns->stat, tkns->sbsh); */
 /* 		printf("\n----NEXT TOKEN----\n"); */
 /* 		tkns = tkns->next; */
 /* 	} */
 /* 	return (0); */
 /* } */
