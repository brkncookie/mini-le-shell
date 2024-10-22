/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:14 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:40:15 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((s1[i] || s2[j]) && i < n && j < n)
	{
		if (s1[i] == '\'' || s1[i] == '\"')
		{
			i++;
			continue ;
		}
		if (s2[j] == '\'' || s2[j] == '\"')
		{
			j++;
			continue ;
		}
		if (s1[i] != s2[j])
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		i++;
		j++;
	}
	return (0);
}

/*
int main()
{
    printf("%d\n", ft_strncmp("bru", "bru", 9));
    printf("%d\n", strncmp("bru", "bru", 9));
}
*/
