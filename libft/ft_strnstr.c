/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:22 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:40:25 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	c;
	size_t	needl_len;
	char	*str;

	i = 0;
	str = (char *)haystack;
	needl_len = ft_strlen(needle);
	if (n == 0 && (str == NULL || needle == NULL))
		return (NULL);
	if (needl_len == 0 || haystack == needle)
		return (str);
	while (str[i] && i < n)
	{
		c = 0;
		while (str[i + c] && needle[c]
			&& str[i + c] == needle[c] && i + c < n)
			c++;
		if (c == needl_len)
			return (str + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
    printf("%s\n", strstr("bruh stop here pls", "here"));
    printf("%s\n", ft_strnstr("bruh stop here pls", "hegh", 2));
}
*/
