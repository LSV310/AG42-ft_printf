/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:03:27 by agruet            #+#    #+#             */
/*   Updated: 2024/11/22 17:08:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int	ft_printf(const char *, ...);
int	ft_putnbr_base(unsigned int n, char *base, int base_len);
int	ft_putnbr_hex(int n, char *base);
static int	ft_printptr(unsigned long long ptr);

#endif
