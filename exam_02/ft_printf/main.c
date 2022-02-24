/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:47:34 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/14 20:22:51 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int a = 0;
	int b = 0;
	
	// a = printf("truc || %d ||truc\n", -2147483647);
	// b = ft_printf("truc || %d ||truc\n", -2147483647);
	// printf("printf: %d || ft_printf: %d", a, b);
	
	// a = printf("truc || %s ||truc\n", "truc bidule truc \n");
	// b = ft_printf("truc || %s ||truc\n", "truc bidule truc \n");
	// printf("printf: %d || ft_printf: %d", a, b);
	
	a = printf("%x %x %x %x\n", INT_MAX, INT_MIN, 0, -42);
	b = ft_printf("%x %x %x %x\n", INT_MAX, INT_MIN, 0, -42);
	a = printf("%x\n", 0);
	b = ft_printf("%x\n",0);
	printf("printf: %d\nft_printf: %d", a, b);
}