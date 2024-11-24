/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:25:18 by agruet            #+#    #+#             */
/*   Updated: 2024/11/24 21:14:14 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	ft_printf("------------\n");
	ft_printf("OG: %d\n", printf("%c\n", '?'));
	ft_printf("ME: %d\n", ft_printf("%c\n", '?'));
	ft_printf("OG: %d\n", printf("s: %s\n", "salut"));
	ft_printf("ME: %d\n", ft_printf("s: %s\n", "salut"));
	ft_printf("OG: %d\n", printf("p: %p\n", "pointtteerrr"));
	ft_printf("ME: %d\n", ft_printf("p: %p\n", "pointtteerrr"));
	ft_printf("OG: %d\n", printf("d: %d\n", 42));
	ft_printf("ME: %d\n", ft_printf("d: %d\n", 42));
	ft_printf("OG: %d\n", printf("i: %i\n", 2147483647));
	ft_printf("ME: %d\n", ft_printf("i: %i\n", 2147483647));
	ft_printf("OG: %d\n", printf("u: %lu\n", 2147483648));
	ft_printf("ME: %d\n", ft_printf("u: %u\n", 2147483648));
	ft_printf("OG: %d\n", printf("x: %x\n", 42));
	ft_printf("ME: %d\n", ft_printf("x: %x\n", 42));
	ft_printf("OG: %d\n", printf("X: %X\n", 42));
	ft_printf("ME: %d\n", ft_printf("X: %X\n", 42));
	ft_printf("OG: %d\n", printf("%%: %%\n"));
	ft_printf("ME: %d\n", ft_printf("%%: %%\n"));
	ft_printf("------------\n");
	return (0);
}
