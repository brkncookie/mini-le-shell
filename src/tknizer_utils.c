/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnadir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:49:16 by mnadir            #+#    #+#             */
/*   Updated: 2023/01/19 09:28:21 by mnadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	is_blncd(char *str, char c)
{
	char	tmp;

	if (c)
		while (*str && *str != c)
			str++;
	if (c)
		return (!(*str == 0));
	while (*str)
	{
		tmp = *str;
		if (tmp == '\'' || tmp == '\"' || tmp == '(')
		{
			if (tmp == '(')
				tmp = ')';
			if (is_blncd(str + 1, tmp) && str++)
				while (*str && *str != tmp)
					str++;
			else
				return (0);
		}
		else if (tmp == ')')
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%d\n", is_blncd(argv[1], 0));
	return (0);
}
