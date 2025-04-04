/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:03:13 by agruet            #+#    #+#             */
/*   Updated: 2025/04/04 17:48:47 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_struct(t_printf *ft_print, char *str)
{
	ft_print->str = str;
	ft_print->str_len = ft_strlen(ft_print->str);
	ft_print->buff_size = PRINTF_BUFF_SIZE;
	ft_print->buff_pos = 0;
	ft_memset(ft_print->buff, 0, ft_print->buff_size);
	ft_print->current = 0;
	ft_print->fd = 1;
	ft_print->len = 0;
	ft_print->flags = NO_FLAGS;
	ft_print->padding = 0;
	ft_print->precision = 0;
}

void	start_conversion(t_printf *ft_print, char *str, va_list ap)
{
	ft_print->current += 1;
	if (!parse_flags(ft_print, str, ft_print->current))
	{
		printf("\tflags: %d\n", ft_print->flags);
		printf("\tprecision: %d\n", ft_print->precision);
		printf("\tpadding: %d\n", ft_print->padding);
		write_to_buff(ft_print, "%", 1);
		reset_flags(ft_print);
		return ;
	}
	printf("\tflags: %d\n", ft_print->flags);
	printf("\tprecision: %d\n", ft_print->precision);
	printf("\tpadding: %d\n", ft_print->padding);
	if (str[ft_print->current] == 'c')
		write_char(ft_print, va_arg(ap, int));
	else if (str[ft_print->current] == 's')
		write_str(ft_print, va_arg(ap, char *));
	else if (str[ft_print->current] == 'p')
		write_ptr(ft_print, va_arg(ap, unsigned long long));
	else if (str[ft_print->current] == 'd' || str[ft_print->current] == 'i')
		write_int(ft_print, va_arg(ap, int), BASE_10, 10);
	else if (str[ft_print->current] == 'u')
		write_uint(ft_print, va_arg(ap, unsigned int), BASE_10, 10);
	else if (str[ft_print->current] == 'x')
		write_uint(ft_print, va_arg(ap, unsigned int), BASE_16L, 16);
	else if (str[ft_print->current] == 'X')
		write_uint(ft_print, va_arg(ap, unsigned int), BASE_16U, 16);
	else
		write_to_buff(ft_print, "%", 1);
	ft_print->current += 1;
	reset_flags(ft_print);
}

int	ft_printf(const char *str, ...)
{
	t_printf	ft_print;
	size_t		count;

	if (!str)
		return (-1);
	init_struct(&ft_print, (char *)str);
	va_start(ft_print.ap, str);
	while (ft_print.current < ft_print.str_len && ft_print.len >= 0)
	{
		if (str[ft_print.current] == '%')
			start_conversion(&ft_print, ft_print.str, ft_print.ap);
		else
		{
			count = ft_print.current;
			while (count < ft_print.str_len && str[count] != '%')
				count++;
			write_to_buff(&ft_print, ft_print.str + ft_print.current,
				count - ft_print.current);
			ft_print.current = count;
		}
	}
	if (ft_print.len >= 0)
		flush_printf(&ft_print);
	va_end(ft_print.ap);
	return (ft_print.len);
}
