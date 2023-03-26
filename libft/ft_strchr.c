/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:39:11 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:39:13 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	if (c == '\0')
		return (str + i);
	return ((void *)0);
}
/*
int main()
{
    printf("%s\n", strchr("bruh pls stop this shitto", '\0'));
    printf("%s\n", ft_strchr("bruh pls stop this shitto", '\0'));
}
*/
