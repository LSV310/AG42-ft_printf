/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:03:13 by agruet            #+#    #+#             */
/*   Updated: 2025/04/03 15:05:15 by agruet           ###   ########.fr       */
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
}

static int	find_convert_sign(t_printf *ft_print, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && ft_strchr(AVAILABLE_PRINTF_FLAGS, str[i]))
		i++;
	j = 0;
	while (ft_isdigit(str[i + j]))
		j++;
	ft_print->padding = ft_atoi(str + i);
	return (i + j);
}

static int	parse_flags(t_printf *ft_print, char *str, size_t current)
{
	size_t	end;

	end = find_convert_sign(ft_print, ft_print->str + current);
	ft_print->current += end;
	if (!str[current + end]
		|| !ft_strchr(AVAILABLE_PRINTF_CONVERT,
			str[current + end]))
		return (0);
	if (ft_strnchr(str + current, '-', end))
		ft_print->flags |= LEFT_JUSTIFY;
	if (ft_strnchr(str + current, '0', end))
		ft_print->flags |= PAD_ZEROS;
	if (ft_strnchr(str + current, '.', end))
		ft_print->flags |= PRECISION;
	if (ft_strnchr(str + current, '#', end))
		ft_print->flags |= ALTERNATIVE_FORM;
	if (ft_strnchr(str + current, '+', end))
		ft_print->flags |= SHOW_SIGN;
	if (ft_strnchr(str + current, ' ', end))
		ft_print->flags |= SPACE_POSITIVE;
	return (1);
}

void	start_conversion(t_printf *ft_print, char *str, va_list ap)
{
	ft_print->current += 1;
	if (!parse_flags(ft_print, str, ft_print->current))
	{
		ft_print->current += 1;
		return ;
	}
	if (str[ft_print->current] == 'c')
		write_char(ft_print, va_arg(ap, int));
	else if (str[ft_print->current] == 's')
		write_string(ft_print, va_arg(ap, char *));
	else if (str[ft_print->current] == 'p')
		write_ptr(ft_print, va_arg(ap, unsigned long long));
	else if (str[ft_print->current] == 'd' || str[ft_print->current] == 'i')
		ft_putnbr_base_len_fd(ft_print, va_arg(ap, int), BASE_10, 10);
	else if (str[ft_print->current] == 'u')
		ft_putnbr_base_fd(ft_print, va_arg(ap, unsigned int), BASE_10, 10);
	else if (str[ft_print->current] == 'x')
		ft_putnbr_base_fd(ft_print, va_arg(ap, unsigned int), BASE_16L, 16);
	else if (str[ft_print->current] == 'X')
		ft_putnbr_base_fd(ft_print, va_arg(ap, unsigned int), BASE_16U, 16);
	else
		write_to_buff(ft_print, "%", 1);
	ft_print->current += 1;
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
	// printf("%d\n", ft_print.padding);
	va_end(ft_print.ap);
	return (ft_print.len);
}
