/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:16:23 by agruet            #+#    #+#             */
/*   Updated: 2024/11/24 21:29:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_normal_chars(const char *s, int *current)
{
	int	start;
	int	len;

	start = *current;
	while (s[*current] && s[*current] != '%')
		(*current)++;
	len = *current - start;
	write(1, &s[start], len);
	return (len);
}

static int	get_conversion(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar_len(va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr_len(va_arg(ap, char *)));
	else if (c == 'p')
		return (ft_printptr(va_arg(ap, unsigned long long)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base_len(va_arg(ap, unsigned int), "0123456789", 10));
	else if (c == 'u')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", 10));
	else if (c == 'x')
		return (ft_putnbr_base_len(va_arg(ap, int), "0123456789abcdef", 16));
	else if (c == 'X')
		return (ft_putnbr_base_len(va_arg(ap, int), "0123456789ABCDEF", 16));
	else if (c == '%')
		return (ft_putchar_len('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		len;
	int		current;

	if (!s)
		return (-1);
	va_start(ap, s);
	current = 0;
	len = 0;
	while (s[current])
	{
		if (s[current] == '%')
		{
			len += get_conversion(s[current + 1], ap);
			current += 2;
		}
		else
			len += print_normal_chars(s, &current);
	}
	va_end(ap);
	return (len);
}
