/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:39:31 by mnadir            #+#    #+#             */
/*   Updated: 2023/02/04 12:31:53 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	ft_isspace(char c)
{
	return (c == '\n' || c == '\r' || c == '\f' \
			|| c == '\t' || c == '\v' || c == ' ');
}

char	*ft_strndup(const char *s1, size_t l)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s1);
	if(len < l)
		l = len;
	p = ft_calloc(l + 1, sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, l);
	return (p);
}
