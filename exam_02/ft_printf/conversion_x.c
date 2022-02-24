/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:28:12 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/14 20:29:36 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int		count_nbr(unsigned long nb)
{
	int count = 0;
	
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int		ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*convert_nbr(unsigned long nb)
{
	char *res;
	char *base = NULL;
	int	i = 0;

	res = (char *)malloc(sizeof(char) * count_nbr(nb) + 1);
	base = "0123456789abcdef";
	if (nb == 0) // pas oublier le cas 0 --> pas oublier le '\0'
	{
		res[0] = '0'; 
		res[1] = '\0';
	}
	else
	{
		while (nb > 0)
		{
			res[i++] = base[(nb % 16)];
			nb /= 16;
		}
		res[i] = '\0';
		
		i = 0;
		char temp;
		while (i < ft_strlen(res) / 2)
		{
			temp = res[i];
			res[i] = res[ft_strlen(res) - i - 1];
			res[ft_strlen(res) - i - 1] = temp;
			i++;
		}
	}
	return (res);
}

void	conversion_x(va_list ap, int *length)
{
	unsigned long nb;
	char	*res;

	nb = (unsigned long)va_arg(ap, unsigned int); // a caster en unsigned long
	res = convert_nbr(nb);
	ft_putstr(res, length);
	free(res);
	res = NULL;
}
