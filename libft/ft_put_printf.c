/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:01:10 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/12 10:08:58 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstrf(char *s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

void	ft_putnbrf(int nb, int *len)
{
	if (nb == -2147483648)
	{
		*len += ft_putstrf("-2147483648");
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbrf(-nb, len);
		(*len)++;
	}
	else
	{
		if ((nb <= 9) && (nb >= 0))
		{
			ft_putchar(nb + '0');
			(*len)++;
		}
		else
		{
			ft_putnbrf(nb / 10, len);
			ft_putnbrf(nb % 10, len);
		}
	}
}

void	ft_puthex(unsigned long nb, int *len, int bigorsmol)
{
	char	*uphex;
	char	*lowhex;

	lowhex = "0123456789abcdef";
	uphex = "0123456789ABCDEF";
	if (nb < 0)
	{
		ft_putchar('-');
		(*len)++;
		ft_puthex(-nb, len, bigorsmol);
	}
	if (nb < 16)
	{
		if (bigorsmol == 0)
			ft_putchar(lowhex[nb]);
		else
			ft_putchar(uphex[nb]);
		(*len)++;
	}
	else
	{
		ft_puthex(nb / 16, len, bigorsmol);
		ft_puthex(nb % 16, len, bigorsmol);
	}
}

void	ft_put_unsigned(unsigned int nb, int *len)
{
	if ((nb <= 9) && (nb >= 0))
	{
		ft_putchar(nb + '0');
		(*len)++;
	}
	else
	{
		ft_put_unsigned(nb / 10, len);
		ft_put_unsigned(nb % 10, len);
	}
}
