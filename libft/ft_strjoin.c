/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:39:28 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:39:29 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*arr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	arr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (arr == NULL)
		return (0);
	while (i < ft_strlen(s1))
		arr[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		arr[i++] = s2[j++];
	arr[i] = '\0';
	return (arr);
}

/*
#include <stdio.h>
int main()
{
    printf("%s\n", ft_strjoin("bruh iam so", ""));
}
*/
