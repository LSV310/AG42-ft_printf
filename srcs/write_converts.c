/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_converts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:30:11 by agruet            #+#    #+#             */
/*   Updated: 2025/04/04 15:36:25 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_char(t_printf *ft_print, int c)
{
	write_to_buff(ft_print, (char *)&c, 1);
}

void	write_string(t_printf *ft_print, char *str)
{
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

	divisor = 1;
	while (nb / divisor >= b_len)
		divisor *= b_len;
	while (divisor > 0)
	{
		write_to_buff(ft_print, &base[nb / divisor % b_len], 1);
		divisor /= b_len;
	}
}

void	write_int(t_printf *ft_print, int n, char *base, int base_len)
{
	unsigned int	nb;
	unsigned int	divisor;

	nb = n;
	if (n < 0)
	{
		nb = -n;
		write_to_buff(ft_print, "-", 1);
	}
	divisor = 1;
	while (nb / divisor >= base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		write_to_buff(ft_print, &base[nb / divisor % base_len], 1);
		divisor /= base_len;
	}
}

void	write_ptr(t_printf *ft_print, unsigned long long ptr)
{
	size_t	divisor;

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
		write_to_buff(ft_print, &BASE_16L[ptr / divisor % 16], 1);
		divisor /= 16;
	}
}
