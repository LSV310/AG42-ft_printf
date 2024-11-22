/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:16:23 by agruet            #+#    #+#             */
/*   Updated: 2024/11/22 15:54:55 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned int n, char *base, int base_len)
{
	if (n >= (unsigned int)base_len)
		ft_putnbr_base(n / base_len, base, base_len);
	n = base[n % base_len];
	write(1, &n, 1);
}

void	ft_putnbr_hex(int n, char *base)
{
	unsigned int	nb;

	if (n < 0)
	{
		write(1, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	ft_putnbr_base(nb, base, 16);
}

static void	ft_printptr(unsigned long long ptr)
{
	char	*base;
	char	buff[17];
	int		i;

	base = "0123456789";
	i = 0;
	while (ptr > 0)
	{
		buff[i] = base[ptr % 16];
		i++;
		ptr /= 16;
	}
	write(1, "0x", 2);
	while (--i > 0)
	{
		write(1, &buff[i], 1);
	}
}

int	get_conversion(char *s, int nb, va_list ap)
{
	if (nb % 2)
	{
		if (*(s + 1) == 'c')
			ft_putchar_fd(va_arg(ap, int), 1);
		else if (*(s + 1) == 's')
			ft_putstr_fd(va_arg(ap, char *), 1);
		else if (*(s + 1) == 'p')
			ft_printptr(va_arg(ap, unsigned long long));
		else if (*(s + 1) == 'd' || *(s + 1) == 'i')
			ft_putnbr_fd(va_arg(ap, int), 1);
		else if (*(s + 1) == 'u')
			ft_putnbr_base(va_arg(ap, unsigned int), "0123456789", 10);
		else if (*(s + 1) == 'x')
			ft_putnbr_hex(va_arg(ap, int), "0123456789abcdef");
		else if (*(s + 1) == 'X')
			ft_putnbr_hex(va_arg(ap, int), "0123456789ABCDEF");
		else if (*(s + 1) == '%')
			ft_putchar_fd('%', 1);
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		nb;
	va_list	ap;

	i = 0;
	nb = 0;
	if (!s)
		return (-1);
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			get_conversion((char *)s + i, ++nb, ap);
			i++;
		}
		else
		{
			write(1, &s[i], 1);
			nb = 0;
		}
		i++;
	}
	va_end(ap);
	return (0);
}
