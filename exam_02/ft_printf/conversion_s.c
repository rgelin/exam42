/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:01:08 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/14 20:29:56 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *length)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		ft_putchar(str[i]);
		(*length)++;
	}
		
}

void	conversion_s(va_list ap, int *length)
{
	char *str;

	str = va_arg(ap, char *);
	if (!str)
	{
		write(1, "(null)", 6); //pas oublier le cas NULL
		(*length) += 6;
	}
	else
		ft_putstr(str, length);
}