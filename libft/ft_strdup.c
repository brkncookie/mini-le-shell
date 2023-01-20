/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:39:18 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:39:20 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (str == NULL)
		return (0);
	str = ft_memcpy(str, s, ft_strlen(s) + 1);
	return (str);
}
/*
int main ()
{
	printf("%s\n", ft_strdup("bruh copy this"));
}
*/
