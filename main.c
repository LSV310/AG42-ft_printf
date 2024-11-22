/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:25:18 by agruet            #+#    #+#             */
/*   Updated: 2024/11/22 14:43:55 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_printf("------------\nFT_PRINTF:\n");
	ft_printf("c: %c\n", '?');
	ft_printf("s: %s\n", "salut");
	ft_printf("p: %p\n", "pointtteerrr");
	ft_printf("d: %d\n", 42);
	ft_printf("i: %i\n", 2147483647);
	ft_printf("u: %u\n", 2147483648);
	ft_printf("x: %x\n", 42);
	ft_printf("X: %X\n", 42);
	ft_printf("%%: %%\n");
	ft_printf("------------\n");
	return (0);
}
