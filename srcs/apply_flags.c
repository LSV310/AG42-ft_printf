/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:10:17 by agruet            #+#    #+#             */
/*   Updated: 2025/04/07 17:46:27 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	apply_numeric_flag(t_printf *ft_print, int len, char *base, bool is_neg)
{
	if (ft_print->flags ^ PAD_ZEROS && ft_print->flags ^ LEFT_JUSTIFY)
	{
		if (write_padding(ft_print, ft_print->padding - len, ' ') == -1)
			return (-1);
	}
	if (write_sign(ft_print, is_neg) == -1)
		return (-1);
	if (ft_print->flags & ALTERNATIVE_FORM && write_sharp(ft_print, base) == -1)
		return (-1);
	if (ft_print->flags & PAD_ZEROS)
	{
		if (write_padding(ft_print, ft_print->padding - len, '0') == -1)
			return (-1);
	}
	return (0);
}
