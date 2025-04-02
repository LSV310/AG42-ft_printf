/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:30:56 by agruet            #+#    #+#             */
/*   Updated: 2025/04/02 14:44:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

int	flush_printf(t_printf *printf)
{
	if (printf->buff_pos <= 0)
		return (0);
	if (write(printf->fd, printf->buff, printf->buff_pos))
	{
		printf->len = -1;
		return (-1);
	}
	ft_memset(printf->buff, 0, printf->buff_size);
	printf->buff_pos = 0;
	printf->len += printf->buff_pos;
	return (0);
}

static int	fill_write(t_printf *printf, char *to_write)
{
	ft_strlcat(printf->buff, to_write, printf->buff_size + 1);
	if (write(printf->fd, printf->buff, printf->buff_size))
		return (-1);
	printf->buff_pos = 0;
	printf->len += printf->buff_size;
	return (0);
}

int	write_to_buff(t_printf *printf, char *to_write, size_t size)
{
	while (size >= printf->buff_size)
	{
		if (fill_write(printf, to_write) == -1)
			return (-1);
		to_write += printf->buff_size;
		size -= printf->buff_size;
	}
	if (printf->buff_pos + size >= printf->buff_size)
	{
		if (flush_printf(printf) == -1)
			return (-1);
	}
	ft_strlcat(printf->buff, to_write, size);
	printf->buff_pos += size;
	printf->len += size;
	return (0);
}
