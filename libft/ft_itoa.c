/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:35:30 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:35:33 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static int	get_num_of_digits(int i)
{
	int	k;

	k = 0;
	while (i >= 10)
	{
		i /= 10;
		k++;
	}
	return (k);
}

static void	fill_string(int nb, int i, int k, char *arr)
{
	arr[k + 1] = '\0';
	while (k >= 0)
	{
		arr[k] = i % 10 + 48;
		i /= 10;
		k--;
	}
	if (nb < 0)
		arr[0] = '-';
}

char	*ft_itoa(int nb)
{
	long int	i;
	char		*arr;
	int			k;

	i = nb;
	k = 0;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (i < 0)
	{
		i = -i;
		k++;
	}
	k += get_num_of_digits(i);
	arr = (char *)malloc(sizeof(char) * (k + 2));
	if (arr == (NULL))
		return (NULL);
	fill_string(nb, i, k, arr);
	return (arr);
}

// #include<stdio.h>
// int main()
// {
// 	printf("%s\n", ft_itoa(-5859));
// }
