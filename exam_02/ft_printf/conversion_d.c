/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:28:06 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/14 20:30:15 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(long nb, int *length)
{
	if (nb < 0)
	{
		ft_putchar('-');
		(*length)++;
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10, length);
		ft_putchar((nb % 10) + '0');
		(*length)++;
	}
	else
	{
		ft_putchar(nb + '0');
		(*length)++;
		
	}
}

void	conversion_d(va_list ap, int *length)
{
	long nb;

	nb = (long)va_arg(ap, int); // a caster en long
	ft_putnbr(nb, length);
	return ;
}