/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:57 by alemsafi          #+#    #+#             */
/*   Updated: 2022/10/17 16:33:59 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_atoi(const char *str)
{
	long	i;
	int		sign;
	long	acc;
	long	start;

	i = 0;
	sign = 1;
	acc = 0;
	while (str[i] && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	start = i;
	while (str[i] && ft_isdigit(str[i]))
		acc = acc * 10 + (str[i++] - '0');
	if (i - start >= 19)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (acc * sign);
}

// int main()
// {
//     printf("%d\n", ft_atoi("    32344444444444444444444"));
//     printf("%d\n", atoi("    32344444444444444444444"));
// }
