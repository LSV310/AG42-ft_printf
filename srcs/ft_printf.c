/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:03:13 by agruet            #+#    #+#             */
/*   Updated: 2025/04/02 23:59:13 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_struct(t_printf *printf, char *str)
{
	printf->str = str;
	printf->str_len = ft_strlen(printf->str);
	ft_memset(printf->buff, 0, printf->buff_size);
	printf->buff_pos = 0;
	printf->buff_size = PRINTF_BUFF_SIZE;
	printf->current = 0;
	printf->fd = 1;
	printf->len = 0;
	printf->flags = NO_FLAGS;
}

static int	find_convert_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(AVAILABLE_PRINTF_FLAGS, str[i]))
		i++;
	return (i);
}

static int	parse_flags(t_printf *printf)
{
	size_t	end;

	end = find_convert_sign(printf->str + printf->current);
	if (!printf->str[printf->current + end]
		|| !ft_strchr(AVAILABLE_PRINTF_CONVERT,
		printf->str[printf->current + end]))
	{
		printf->current += end;
		return (0);
	}
	if (ft_strnchr(printf->str + printf->current, '-', end))
		printf->flags |= LEFT_JUSTIFY;
	if (ft_strnchr(printf->str + printf->current, '0', end))
		printf->flags |= PAD_ZEROS;
	if (ft_strnchr(printf->str + printf->current, '.', end))
		printf->flags |= PRECISION;
	if (ft_strnchr(printf->str + printf->current, '#', end))
		printf->flags |= ALTERNATIVE_FORM;
	if (ft_strnchr(printf->str + printf->current, '+', end))
		printf->flags |= SHOW_SIGN;
	if (ft_strnchr(printf->str + printf->current, ' ', end))
		printf->flags |= SPACE_POSITIVE;
	printf->current += end;
	return (1);
}

void	start_conversion(t_printf *printf, char *str, va_list ap)
{
	printf->current += 1;
	if (!parse_flags(printf))
		return ;
		if (str[printf->current] == 'c')
		return (ft_putchar_len_fd(va_arg(ap, int), 1));
	else if (str[printf->current] == 's')
		return (ft_putstr_len_fd(va_arg(ap, char *), 1));
	else if (str[printf->current] == 'p')
		return (ft_printptr_fd(va_arg(ap, unsigned long long), 1));
	else if (str[printf->current] == 'd' || str[printf->current] == 'i')
		return (ft_putnbr_base_len_fd(va_arg(ap, int), BASE_10, 10, 1));
	else if (str[printf->current] == 'u')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_10, 10, 1));
	else if (str[printf->current] == 'x')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_16L, 16, 1));
	else if (str[printf->current] == 'X')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), BASE_16U, 16, 1));
	else if (str[printf->current] == '%')
		return (ft_putchar_len_fd('%', 1));
}

int	ft_printf(const char *str, ...)
{
	t_printf	printf;
	size_t		count;

	if (!str)
		return (-1);
	init_struct(&printf, (char *)str);
	va_start(printf.ap, str);
	while (printf.current < printf.str_len && printf.len >= 0)
	{
		if (str[printf.current] == '%')
			start_conversion(&printf, printf.str, printf.ap);
		else
		{
			count = printf.current;
			while (count <= printf.str_len && str[count] != '%')
				count++;
			write_to_buff(&printf, printf.str + printf.current,
				count - printf.current);
		}
	}
	if (printf.len >= 0)
		flush_printf(&printf);
	printf("%d\n", printf.flags);
	va_end(printf.ap);
	return (printf.len);
}
