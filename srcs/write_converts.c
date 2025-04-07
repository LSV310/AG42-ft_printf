/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_converts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:30:11 by agruet            #+#    #+#             */
/*   Updated: 2025/04/07 18:04:32 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_char(t_printf *ft_print, int c)
{
	if (ft_print->flags ^ LEFT_JUSTIFY)
	{
		if (write_padding(ft_print, ft_print->padding - 1, ' ') == -1)
			return ;
	}
	if (write_to_buff(ft_print, (char *)&c, 1) == -1)
		return ;
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - 1, ' ');
}

void	write_str(t_printf *ft_print, char *str)
{
	int	len;

	len = 6;
	if (str)
		len = ft_strlen(str);
	if (ft_print->flags ^ LEFT_JUSTIFY)
	{
		if (write_padding(ft_print, ft_print->padding - len, ' ') == -1)
			return ;
	}
	if (!str)
	{
		if (write_to_buff(ft_print, "(null)", 6) == -1)
			return ;
	}
	else if (write_to_buff(ft_print, str, ft_strlen(str)) == -1)
		return ;
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - len, ' ');
}

void	write_uint(t_printf *ft_print, unsigned int nb, char *base, int b_len)
{
	unsigned int	divisor;
	int				calc_size;

	calc_size = calc_uint_size(ft_print, nb, b_len);
	if (nb == 0 && ft_print->flags & ALTERNATIVE_FORM)
		ft_print->flags ^= ALTERNATIVE_FORM;
	if (apply_numeric_flag(ft_print, calc_size, base, nb < 0) == -1)
		return ;
	divisor = 1;
	while (nb / divisor >= b_len)
		divisor *= b_len;
	while (divisor > 0)
	{
		if (write_to_buff(ft_print, &base[nb / divisor % b_len], 1) == -1)
			return ;
		divisor /= b_len;
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}

void	write_int(t_printf *ft_print, int n, char *base, int base_len)
{
	unsigned int	nb;
	unsigned int	divisor;
	int				calc_size;

	calc_size = calc_int_size(ft_print, n, base_len);
	if (apply_numeric_flag(ft_print, calc_size, base, n < 0) == -1)
		return ;
	nb = n;
	if (n < 0)
		nb = -n;
	divisor = 1;
	while (nb / divisor >= base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		if (write_to_buff(ft_print, &base[nb / divisor % base_len], 1) == -1)
			return ;
		divisor /= base_len;
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}

void	write_ptr(t_printf *ft_print, unsigned long long ptr)
{
	size_t	divisor;
	int		calc_size;

	calc_size = calc_long_size(ft_print, ptr);
	if (apply_numeric_flag(ft_print, calc_size, NULL, ptr < 0) == -1)
		return ;
	if (!ptr)
	{
		write_to_buff(ft_print, "(nil)", 5);
		return ;
	}
	if (write_to_buff(ft_print, "0x", 2) == -1)
		return ;
	divisor = 1;
	while (ptr / divisor >= 16)
		divisor *= 16;
	while (divisor > 0)
	{
		if (write_to_buff(ft_print, &BASE_16L[ptr / divisor % 16], 1) == -1)
			return ;
		divisor /= 16;
	}
	if (ft_print->flags & LEFT_JUSTIFY)
		write_padding(ft_print, ft_print->padding - calc_size, ' ');
}
