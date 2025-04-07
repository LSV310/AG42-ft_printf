/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_padding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:32:38 by agruet            #+#    #+#             */
/*   Updated: 2025/04/07 17:18:01 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	calc_uint_size(t_printf *ft_print, unsigned int nb, int base_len)
{
	int				size;
	unsigned int	divisor;

	size = 1;
	divisor = 1;
	while (nb / divisor >= base_len)
	{
		size++;
		divisor *= base_len;
	}
	if (size < ft_print->precision)
		size = ft_print->precision;
	if (nb != 0 && ft_print->flags & ALTERNATIVE_FORM)
		size += 2;
	return (size);
}

int	calc_int_size(t_printf *ft_print, int n, int base_len)
{
	int				size;
	unsigned int	nb;
	unsigned int	divisor;

	size = 1;
	nb = n;
	if (n < 0)
		nb = -n;
	divisor = 1;
	while (nb / divisor >= base_len)
	{
		size++;
		divisor *= base_len;
	}
	if (size < ft_print->precision)
		size = ft_print->precision;
	if (n < 0 || ft_print->flags & SPACE_POSITIVE || ft_print->flags & SHOW_SIGN)
		size++;
	return (size);
}

int	calc_long_size(t_printf *ft_print, unsigned long long ptr)
{
	size_t	size;
	size_t	divisor;

	if (!ptr)
		return (5);
	divisor = 1;
	size = 1;
	while (ptr / divisor >= 16)
	{
		size++;
		divisor *= 16;
	}
	if (size < ft_print->precision)
		size = ft_print->precision;
	size += 2;
	return (size);
}
