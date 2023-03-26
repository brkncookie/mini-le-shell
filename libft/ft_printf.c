/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:38:51 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/12 10:09:38 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	ap;

	i = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str != '%')
		{
			write(1, str, 1);
			i++;
		}
		else
			ft_check_and_put(*(++str), ap, &i);
		str++;
	}
	va_end(ap);
	return (i);
}

void	ft_check_and_put(char c, va_list ap, int *i)
{
	if (c == 'd' || c == 'i')
		ft_putnbrf((int)va_arg(ap, int), i);
	else if (c == 'c')
		*i += ft_putchar((int)va_arg(ap, int));
	else if (c == 's')
		*i += ft_putstrf(va_arg(ap, char *));
	else if (c == 'p')
	{
		*i += ft_putstrf("0x");
		ft_puthex((unsigned long)va_arg(ap, char *), i, 0);
	}
	else if (c == 'x')
		ft_puthex((unsigned int)va_arg(ap, char *), i, 0);
	else if (c == 'X')
		ft_puthex((unsigned int)va_arg(ap, char *), i, 1);
	else if (c == 'u')
		ft_put_unsigned((unsigned int)va_arg(ap, unsigned int), i);
	else if (c == '%')
		*i += ft_putchar('%');
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
