/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:07:58 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/01 23:49:42 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int ac, char *av[])
{
	int i;
	int j;
	int	used[127];
	// int	len;
	(void)av;
	
	if (ac != 3)
	{
		write(1, "\n", 1);
		return (-1);
	}
	i = 0;
	j = 0;
	while (i++ < 127)
		used[i] = 0;
	i = 1;
	while (i < 3)
	{
		j = 0;
		while (av[i][j])
		{	
			if (used[(int)av[i][j]] == 0)
			{
				write(1, &av[i][j], 1);
				used[(int)av[i][j]] = 1;
			}
			j++;
		}
		i++;
	}		
	write (1, "\n", 1);
}
