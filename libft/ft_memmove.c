/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:47 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:37:47 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	if (dest == src)
		return (dest);
	if (dest != NULL || src != NULL)
	{
		if (s2 < s1)
		{
			while (n--)
				s1[n] = s2[n];
			return (dest);
		}
		while (n--)
			*s1++ = *s2++;
		return (dest);
	}
	return (NULL);
}
/*
int main()
{
	char cdest[] = "pls stop";
	char cdest2[] = "pls stop";
	char *str;
	str = cdest + 4;
	char *str2;
	str2 = cdest2 + 4;
	memmove(str, cdest, 5);
	printf("Correct string is %s\n", str);
	ft_memmove(str2, cdest2, 5);
	printf("Copied string is %s\n", str2);
}*/
