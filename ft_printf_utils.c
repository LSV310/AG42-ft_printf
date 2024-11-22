/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:51 by agruet            #+#    #+#             */
/*   Updated: 2024/11/22 17:05:34 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned int n, char *base, int base_len)
{
	if (n >= (unsigned int)base_len)
		ft_putnbr_base(n / base_len, base, base_len);
	n = base[n % base_len];
	write(1, &n, 1);
	return ((int)n);
}

int	ft_putnbr_hex(int n, char *base)
{
	unsigned int	nb;

	if (n < 0)
	{
		write(1, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	return (ft_putnbr_base(nb, base, 16));
}

static int	ft_printptr(unsigned long long ptr)
{
	char	*base;
	char	buff[17];
	int		i;
	int		j;

	base = "0123456789";
	i = 0;
	while (ptr > 0)
	{
		buff[i] = base[ptr % 16];
		i++;
		ptr /= 16;
	}
	j = i;
	write(1, "0x", 2);
	while (--i > 0)
	{
		write(1, &buff[i], 1);
	}
	return (j);
}
