/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:17:33 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/14 20:03:24 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

void	ft_putchar(char c);
void	ft_putstr(char *str, int *length);
void	conversion_d(va_list ap, int *length);
void	conversion_s(va_list ap, int *length);
void	conversion_x(va_list ap, int *length);

#endif