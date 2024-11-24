/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:03:27 by agruet            #+#    #+#             */
/*   Updated: 2024/11/24 21:23:23 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int	ft_printf(const char *s, ...);
int	ft_putchar_len(int c);
int	ft_putstr_len(char *s);
int	ft_putnbr_base(unsigned int n, char *base, int base_len);
int	ft_putnbr_base_len(int n, char *base, int base_len);
int	ft_printptr(unsigned long long ptr);

#endif
