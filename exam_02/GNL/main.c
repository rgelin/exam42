/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:20:23 by rgelin            #+#    #+#             */
/*   Updated: 2021/10/18 16:42:06 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL.h"
#include <stdio.h>

int main()
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
		// line = get_next_line(fd);
		// printf("%s", line);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free (line);
		if (!line)
			break ;
	}
}