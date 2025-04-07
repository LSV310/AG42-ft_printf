/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:03:27 by agruet            #+#    #+#             */
/*   Updated: 2025/04/07 16:39:24 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define PRINTF_BUFF_SIZE 1024
# define AVAILABLE_PRINTF_CONVERT "cspdiuxX%"
# define AVAILABLE_PRINTF_FLAGS "-0.# +"

typedef enum printf_flags
{
	INVALID = -1,
	NO_FLAGS = 0,
	LEFT_JUSTIFY = 1 << 0,
	PAD_ZEROS = 1 << 1,
	PRECISION = 1 << 2,
	ALTERNATIVE_FORM = 1 << 3,
	SHOW_SIGN = 1 << 4,
	SPACE_POSITIVE = 1 << 5
}	t_pflags;

typedef struct s_printf
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
	int			padding;
	int			precision;
}	t_printf;

// ft_printf
int		ft_printf(const char *s, ...);

// convertion formats
void	write_char(t_printf *ft_print, int c);
void	write_str(t_printf *ft_print, char *str);
void	write_ptr(t_printf *ft_print, unsigned long long ptr);
void	write_int(t_printf *ft_print, int n, char *base, int base_len);
void	write_uint(t_printf *ft_print, unsigned int nb, char *base, int b_len);

// buffer
int		write_to_buff(t_printf *ft_print, char *to_write, size_t size);
int		flush_printf(t_printf *ft_print);

// parse flags
int		parse_flags(t_printf *ft_print, char *str, size_t current);
void	reset_flags(t_printf *ft_print);

// apply flags
int		apply_numeric_flag(t_printf *ft_print, int len, char *base, bool is_neg);

// calc padding
int		calc_uint_size(t_printf *ft_print, unsigned int nb, int base_len);
int		calc_int_size(t_printf *ft_print, int n, int base_len);
int		calc_long_size(t_printf *ft_print, unsigned long long ptr);

// write_flags
int		write_padding(t_printf *ft_print, int padding, int c);
int		write_sharp(t_printf *ft_print, char *base);
int		write_sign(t_printf *ft_print, bool is_neg);

#endif
