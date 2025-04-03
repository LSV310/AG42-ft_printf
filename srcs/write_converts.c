/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_converts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:30:11 by agruet            #+#    #+#             */
/*   Updated: 2025/04/03 16:49:59 by agruet           ###   ########.fr       */
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

void	ft_putnbr_base_fd(t_printf *ft_print, unsigned int n, char *base, int base_len)
{
	static int	result;

	result = 0;
	if (n >= (unsigned int)base_len)
		ft_putnbr_base_fd(ft_print, n / base_len, base, base_len);
	n = base[n % (unsigned int)base_len];
	write_to_buff(ft_print, (char *)&n, 1);
	result++;
}

void	ft_putnbr_base_len_fd(t_printf *ft_print, int n, char *base, int base_len)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		write_to_buff(ft_print, "-", 1);
	}
	else
		nb = n;
	ft_putnbr_base_fd(ft_print, nb, base, base_len);
}

void	write_ptr(t_printf *ft_print, unsigned long long ptr)
{
	char	buff[17];
	int		i;
	int		result;

	if (!ptr)
	{
		write_to_buff(ft_print, "(nil)", 5);
		return ;
	}
	i = 0;
	while (ptr > 0)
	{
		buff[i] = BASE_16L[ptr % 16];
		i++;
		ptr /= 16;
	}
	result = i;
	if (write_to_buff(ft_print, "0x", 2) == -1)
		return ;
	while (--i >= 0)
		write_to_buff(ft_print, &buff[i], 1);
}
