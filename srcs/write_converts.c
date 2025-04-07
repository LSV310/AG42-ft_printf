/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_converts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:30:11 by agruet            #+#    #+#             */
/*   Updated: 2025/04/07 15:28:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_char(t_printf *ft_print, int c)
{
	if (write_padding(ft_print, ft_print->padding, ' ') == -1)
		return ;
	write_to_buff(ft_print, (char *)&c, 1);
}

void	write_str(t_printf *ft_print, char *str)
{
	if (write_padding(ft_print, ft_print->padding, ' ') == -1)
		return ;
	if (!str)
	{
		write_to_buff(ft_print, "(null)", 6);
		return ;
	}
	write_to_buff(ft_print, str, ft_strlen(str));
}

void	write_uint(t_printf *ft_print, unsigned int nb, char *base, int b_len)
{
	unsigned int	divisor;

	if (apply_numeric_flag(ft_print, 0, base, nb < 0) == -1)
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
}

void	write_int(t_printf *ft_print, int n, char *base, int base_len)
{
	unsigned int	nb;
	unsigned int	divisor;

	if (apply_numeric_flag(ft_print, 0, base, n < 0) == -1)
		return ;
	nb = n;
	if (n < 0)
	{
		nb = -n;
		if (write_to_buff(ft_print, "-", 1))
			return ;
	}
	divisor = 1;
	while (nb / divisor >= base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		if (write_to_buff(ft_print, &base[nb / divisor % base_len], 1) == -1)
			return ;
		divisor /= base_len;
	}
}

void	write_ptr(t_printf *ft_print, unsigned long long ptr)
{
	size_t	divisor;

	if (apply_numeric_flag(ft_print, 0, NULL, ptr < 0) == -1)
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
}
