/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:00:35 by agruet            #+#    #+#             */
/*   Updated: 2025/04/07 17:11:29 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_sharp(t_printf *ft_print, char *base)
{
	if (ft_strcmp(base, BASE_16L) == 0)
		return (write_to_buff(ft_print, "0x", 2));
	else if (ft_strcmp(base, BASE_16U) == 0)
		return (write_to_buff(ft_print, "0X", 2));
	return (0);
}

int	write_sign(t_printf *ft_print, bool is_neg)
{
	if (is_neg)
		return (write_to_buff(ft_print, "-", 1));
	if (ft_print->flags & SHOW_SIGN)
		return (write_to_buff(ft_print, "+", 1));
	if (ft_print->flags & SPACE_POSITIVE)
		return (write_to_buff(ft_print, " ", 1));
	return (0);
}

int	write_padding(t_printf *ft_print, int padding, int c)
{
	int	i;

	i = 0;
	while (i < padding)
	{
		if (write_to_buff(ft_print, (char *)&c, 1) == -1)
			return (-1);
		i++;
	}
	if (padding < 0)
		padding = 0;
	return (padding);
}
