/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:50:05 by agruet            #+#    #+#             */
/*   Updated: 2025/04/07 11:41:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_flags(t_printf *ft_print)
{
	ft_print->flags = NO_FLAGS;
	ft_print->padding = 0;
	ft_print->precision = 0;
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
	return (INVALID);
}

static int	add_precision(t_printf *ft_print, char *str, size_t *current)
{
	size_t	end;

	if (str[*current] != '.')
		return (1);
	ft_print->flags |= PRECISION;
	end = (*current) + 1;
	while (str[end] && ft_isdigit(str[end]))
		end++;
	ft_print->precision = ft_atoi(str + (*current) + 1);
	*current = end;
	return (1);
}

static void	add_padding(t_printf *ft_print, char *str, size_t *current)
{
	size_t	end;

	if (!str[*current])
		return ;
	end = (*current);
	while (str[end] && ft_isdigit(str[end]))
		end++;
	ft_print->padding = ft_atoi(str + *current);
	*current = end;
}

int	parse_flags(t_printf *ft_print, char *str, size_t current)
{
	t_pflags	current_flag;

	if (!str[current])
		return (0);
	current_flag = get_flag(str[current]);
	while (current_flag != INVALID)
	{
		if (current_flag == PRECISION && add_precision(ft_print, str, &current))
			break ;
		ft_print->flags |= current_flag;
		current++;
		current_flag = get_flag(str[current]);
	}
	add_padding(ft_print, str, &current);
	if (!(ft_print->flags & PRECISION))
		add_precision(ft_print, str, &current);
	if (!str[current] || !ft_strchr(AVAILABLE_PRINTF_CONVERT, str[current]))
		return (0);
	ft_print->current = current;
	return (1);
}
