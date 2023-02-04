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
		if (*cmds == ' ')
			tkn_link(&tkns, tkn_create(&cmds, WHITE_SPC));
		else if (*cmds == '\'')
			tkn_link(&tkns, tkn_create(&cmds, QUOTE));
		else if (*cmds == '\"')
			tkn_link(&tkns, tkn_create(&cmds, DQUOTE));
		else if (*cmds == '$')
			tkn_link(&tkns, tkn_create(&cmds, VAR));
		else if (*cmds == '(')
			tkn_link(&tkns, tkn_create(&cmds, OPAR));
		else if (*cmds == ')')
			tkn_link(&tkns, tkn_create(&cmds, CPAR));
		else if (*cmds == '|' && *(cmds + 1) == '|')
			tkn_link(&tkns, tkn_create(&cmds, OR));
		else if (*cmds == '|')
			tkn_link(&tkns, tkn_create(&cmds, PIPE));
		else if (*cmds == '&' && *(cmds + 1) == '&')
			tkn_link(&tkns, tkn_create(&cmds, AND));
		else if (*cmds == '>' && *(cmds + 1) == '>')
			tkn_link(&tkns, tkn_create(&cmds, APPEND));
		else if (*cmds == '>')
			tkn_link(&tkns, tkn_create(&cmds, REDR_O));
		else if (*cmds == '<' && *(cmds + 1) == '<')
			tkn_link(&tkns, tkn_create(&cmds, HERE_DOC));
		else if (*cmds == '<')
			tkn_link(&tkns, tkn_create(&cmds, REDR_I));
		else
			tkn_link(&tkns, tkn_create(&cmds, WORD));
	}
	return (tkns);
	//WILL need to add return value to tkn_link to return NULL in case of error
}

// int	main(int argc, char **argv)
// {
// 	t_tkns	*tkns;
// 	int		i;

// 	(void)argc;
// 	tkns = tokenize(argv[1]);
// 	while (tkns)
// 	{
// 		i = 0;
// 		while (i < tkns->len)
// 			printf("%c", tkns->val[i++]);
// 		printf("\n%d\n%d\n%d", tkns->type, tkns->stat, tkns->sbsh);
// 		printf("\n----NEXT TOKEN----\n");
// 		tkns = tkns->next;
// 	}
// 	return (0);
// }

