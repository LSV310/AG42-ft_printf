/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:50:05 by agruet            #+#    #+#             */
/*   Updated: 2025/04/04 14:32:42 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_flags(t_printf *ft_print)
{
	ft_print->flags = NO_FLAGS;
	ft_print->padding = 0;
}

static t_pflags	get_flag(char c)
{
	if (c == '-')
		return (LEFT_JUSTIFY);
	if (c == '0')
		return (PAD_ZEROS);
	if (c == '.')
		return (PRECISION);
	if (c == '#')
		return (ALTERNATIVE_FORM);
	if (c == '+')
		return (SHOW_SIGN);
	if (c == ' ')
		return (SPACE_POSITIVE);
	if (ft_strchr(AVAILABLE_PRINTF_CONVERT, c))
		return (NO_FLAGS);
	return (INVALID);
}

int	parse_flags(t_printf *ft_print, char *str, size_t current)
{
	size_t		i;
	t_pflags	current_flag;

	if (!str[current])
		return (0);
	current_flag = get_flag(str[current]);
	while (current_flag != INVALID && current_flag != NO_FLAGS)
	{
		if (current_flag && ft_print->flags & current_flag)
			return (0);
		ft_print->flags |= current_flag;
		current++;
		current_flag = get_flag(str[current]);
	}
	if (current_flag == INVALID && !ft_isdigit(str[current]))
		return (0);
	i = 0;
	while (ft_isdigit(str[current + i]))
		i++;
	if (!ft_strchr(AVAILABLE_PRINTF_CONVERT, str[current + i]))
		return (0);
	ft_print->padding = ft_atoi(str + current);
	ft_print->current = current + i;
	return (1);
}
