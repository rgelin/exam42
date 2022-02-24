/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:18:59 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/14 20:02:15 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	to_print(va_list ap, const char *format, int *length)
{
	int i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'd')
				conversion_d(ap, length);
			if (format[i] == 's')
				conversion_s(ap, length);
			if (format[i] == 'x')
				conversion_x(ap, length);
		}
		else
		{
			ft_putchar(format[i]);
			(*length)++;
		}
	}
}

int	ft_printf(const char *format, ...)
{
	int length;

	length = 0;
	va_list(ap);
	va_start(ap, format);
	to_print(ap, format, &length);
	va_end(ap);
	return (length);
}