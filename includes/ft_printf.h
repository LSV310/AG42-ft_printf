/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:03:27 by agruet            #+#    #+#             */
/*   Updated: 2025/04/02 23:46:26 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

#  define PRINTF_BUFF_SIZE 1024
#  define AVAILABLE_PRINTF_CONVERT "cspdiuxX%"
#  define AVAILABLE_PRINTF_FLAGS "-0.# +"

typedef enum printf_flags
{
	NO_FLAGS = 0,
	LEFT_JUSTIFY = 1 << 0,
	PAD_ZEROS = 1 << 1,
	PRECISION = 1 << 2,
	ALTERNATIVE_FORM = 1 << 3,
	SHOW_SIGN = 1 << 4,
	SPACE_POSITIVE = 1 << 5
}	t_pflags;

typedef struct	s_printf
{
	va_list		ap;
	char		*str;
	char		buff[PRINTF_BUFF_SIZE];
	size_t		buff_size;
	size_t		buff_pos;
	size_t		current;
	size_t		str_len;
	int			fd;
	int			len;
	t_pflags	flags;
}	t_printf;

int	ft_printf(const char *s, ...);
int	write_to_buff(t_printf *printf, char *to_write, size_t size);
int	flush_printf(t_printf *printf);

#endif
