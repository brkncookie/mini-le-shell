/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:34 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:40:35 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last_match;
	char	*str;

	i = 0;
	last_match = -1;
	str = (char *)s;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			last_match = i;
		i++;
	}
	if (c == '\0')
		last_match = i;
	if (last_match == -1)
		return ((void *)0);
	str += last_match;
	return (str);
}
/*
int main()
{
    printf("%s\n", ft_strrchr("bruh pls stop fumo", 'o'));
    printf("%s\n", strrchr("bruh pls stop fumo", 'o'));
}
*/
