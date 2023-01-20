/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:50 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:40:51 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	should_alloc;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		should_alloc = ft_strlen(s) - start + 1;
	else
		should_alloc = len + 1;
	str = (char *)malloc(sizeof(char) * should_alloc);
	if (str == NULL)
		return (0);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
#include <stdio.h>

int main()
{
	printf("%s\n", ft_substr("bruh this is so fumo", 2, 6));
}
*/
