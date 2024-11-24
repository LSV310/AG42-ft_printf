/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:51 by agruet            #+#    #+#             */
/*   Updated: 2024/11/24 21:15:00 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_len(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putstr_len(char	*s)
{
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	ft_putnbr_base(unsigned int n, char *base, int base_len)
{
	static int	i;

	i = 0;
	if (n >= (unsigned int)base_len)
		ft_putnbr_base(n / base_len, base, base_len);
	n = base[n % base_len];
	write(1, &n, 1);
	i++;
	return (i);
}

int	ft_putnbr_base_len(int n, char *base, int base_len)
{
	unsigned int	nb;
	unsigned int	is_neg;

	is_neg = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		nb = -n;
		is_neg = 1;
	}
	else
		nb = n;
	return (ft_putnbr_base(nb, base, base_len) + is_neg);
}

int	ft_printptr(unsigned long long ptr)
{
	char	*base;
	char	buff[17];
	int		i;
	int		j;

	base = "0123456789abcdef";
	i = 0;
	while (ptr > 0)
	{
		buff[i] = base[ptr % 16];
		i++;
		ptr /= 16;
	}
	j = i;
	write(1, "0x", 2);
	while (--i >= 0)
		write(1, &buff[i], 1);
	return (j + 2);
}
