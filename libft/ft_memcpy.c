/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:40 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:37:40 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	i = 0;
	if (dest != NULL || src != NULL)
	{
		s1 = (unsigned char *)dest;
		s2 = (unsigned char *)src;
		if (s1 == s2)
			return (s1);
		while (i < n)
		{
			s1[i] = s2[i];
			i++;
		}
		return (dest);
	}
	return (NULL);
}
// #include <string.h>
// int main()
// {
//    printf("%s ",ft_memcpy("hamza","hamza",-1));
//    printf("%s",memcpy("hamza","hamza",-1));
// }
/*
int main()
{
   char cdest[] = "Geeksforbruh";
   char *str;
   str = ft_memcpy(cdest, cdest+8, 4);
   printf("Copied string is %s\n", cdest);
   printf("Copied string is %s", str);

   int isrc[] = {10, 20, 30, 40, 50};
   int n = sizeof(isrc)/sizeof(isrc[0]);
   int idest[n];
   int i;
   int *arr;
   arr = ft_memcpy(idest, isrc,  sizeof(isrc));
   printf("\nCopied array is ");
   for (i=0; i<n; i++)
   {
    printf("%d ", idest[i]);
    printf("%d ", arr[i]);
   }
   return 0;
}
*/
