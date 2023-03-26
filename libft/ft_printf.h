/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:38:38 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/12 10:09:51 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_check_and_put(char c, va_list ap, int *i);
void	ft_put_unsigned(unsigned int nb, int *len);
void	ft_puthex(unsigned long nb, int *len, int bigorsmol);
void	ft_putnbrf(int nb, int *len);
int		ft_putchar(char c);
int		ft_putstrf(char *s);
int		ft_strlen(const char *str);

#endif