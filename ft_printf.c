/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:16:23 by agruet            #+#    #+#             */
/*   Updated: 2024/11/22 17:08:46 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_conversion(char c, va_list ap)
{
	if (c == 'c')
		return(ft_putchar_fd(va_arg(ap, int), 1));
	else if (c == 's')
		return(ft_putstr_fd(va_arg(ap, char *), 1));
	else if (c == 'p')
		return(ft_printptr(va_arg(ap, unsigned long long)));
	else if (c == 'd' || c == 'i')
		return(ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", 10));
	else if (c == 'u')
		return(ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", 10));
	else if (c == 'x')
		return(ft_putnbr_hex(va_arg(ap, int), "0123456789abcdef"));
	else if (c == 'X')
		return(ft_putnbr_hex(va_arg(ap, int), "0123456789ABCDEF"));
	else if (c == '%')
		return(ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (-1);
	va_start(ap, s);
	while (s[i])
	{
		j = i;
		if (s[i] == '%')
		{
			get_conversion(s[i + 1], ap);
			i += 2;
		}
		else
		{
			while (s[i] && s[i] != '%')
				i++;
			write(1, &s[i], i - j);
		}
	}
	va_end(ap);
	return (0);
}
