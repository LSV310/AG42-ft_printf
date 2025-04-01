/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:03:13 by agruet            #+#    #+#             */
/*   Updated: 2025/04/01 16:54:15 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *str, ...)
{
	t_printf	printf;
	va_list		ap;
	int			current;

	if (!str)
		return (-1);
	va_start(ap, str);
	ft_memset(str, 0, printf.buff_size);
	while (current)
	va_end(ap);
}
