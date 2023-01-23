/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:23:15 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/23 13:27:08 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_tree
{
	t_tkns	*tkn;
	t_tree	*limn;
	t_tree	*lisr;
}		t_tree;
#endif
