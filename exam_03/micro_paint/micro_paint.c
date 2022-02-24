/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:28:06 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/24 23:05:10 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

typedef struct s_zone
{
	int		width;
	int		heigth;
	char	draw_char;
}	t_zone;

typedef struct s_figure
{
	char	**draw_zone;
	char	r_char;
	float	Xtl;
	float	Ytl;
	float	Xbr;
	float	Ybr;
	float	width;
	float	heigth;
	char	fig_char;
}	t_figure;

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_free(t_figure *figure)
{
	int i;

	i = -1;
	if (figure)
	{
		while (figure->draw_zone[++i])
		{
			if (figure->draw_zone[i])
				free(figure->draw_zone[i]);
		}
		free(figure->draw_zone);
	}
}
int		ft_perror(t_figure *figure, char *msg_error, int return_value)
{
	int i;

	i = -1;
	if (figure)
		ft_free(figure);
	if (msg_error)
		write(1, msg_error, ft_strlen(msg_error));
	return (return_value);
}

void	print_draw_zone(t_figure *figure)
{
	int	i;
	int	j;

	i = -1;
	while (figure->draw_zone[++i])
	{
		j = -1;
		while (figure->draw_zone[i][++j])
			write(1, &figure->draw_zone[i][j], 1);
		write(1, "\n", 1);
	}
}

int	get_draw_zone(t_zone *zone, t_figure *figure)
{
	int	i;
	int	j;

	i = -1;
	figure->draw_zone = malloc(sizeof(char *) * (zone->heigth + 1));
	if (!figure->draw_zone)
		return (ft_perror(NULL, "Error: malloc\n", 1));
	while (++i < zone->heigth)
	{
		j = -1;
		figure->draw_zone[i] = malloc(sizeof(char) * (zone->width + 1));
		if (!figure->draw_zone[i])
			return (ft_perror(figure, "Error: malloc\n", 1));
		while (++j < zone->width)
			figure->draw_zone[i][j] = zone->draw_char;
		figure->draw_zone[i][j] = '\0';
	}
	figure->draw_zone[i] = NULL;
	return (0);
}

int	get_zone(FILE *file, t_zone *zone, t_figure *figure)
{
	int	ret;
	int	i;

	i = -1;
	ret = fscanf(file, " %d %d %c", &zone->width, &zone->heigth, &zone->draw_char);
	if (ret == 3)
	{
		if (zone->width <= 0 || zone->width > 300 || zone->heigth <= 0 || zone->heigth > 300)
			return (ft_perror(NULL, "Error: Operation file corrupted\n", 1));
		if (get_draw_zone(zone, figure))
			return (1);
		return (0);
	}
	return (ft_perror(NULL, "Error: Operation file corrupted\n", 1));
}


// Hint:
// If a point is defined as (Xa, Ya)
// And a rectangle with a top left corner (Xtl, Ytl) and a bottom right corner (Xbr, Ybr)
// If Xtl <= Xa <= Xbr and Ytl <= Ya <= Ybr then the point is in the rectangle


//Ybr = Ytl + heigth
//Xbr = Xtl + width

void	put_figure_on_draw_zone(t_figure *figure)
{
	int	i;
	int	j;
	// float distance;
	
	i = -1;
	while (figure->draw_zone[++i])
	{
		j = -1;
		while (figure->draw_zone[i][++j])
		{
			if (figure->r_char == 'R' && (figure->Xtl <= (float)j && (float)j <= figure->Xbr) && (figure->Ytl <= (float)i && (float)i <= figure->Ybr))
				figure->draw_zone[i][j] = figure->fig_char;
			if (figure->r_char == 'r')
			{
				if ((figure->Xtl <= (float)j && (float)j <= figure->Xbr) && (figure->Ytl <= (float)i && (float)i <= figure->Ybr)
					&& ((float)j - figure->Xtl < (float)1))
					figure->draw_zone[i][j] = figure->fig_char;
				// if (((j <=  figure->Xtl && j + 1 >= figure->Xtl) && (i >= figure->Ytl && i <= figure->Ybr)))
				// 	figure->draw_zone[i][j] = figure->fig_char;
				// if (((j <=  figure->Xbr && j + 1 >= figure->Xbr) && (i >= figure->Ytl && i <= figure->Ybr)))
				// 	figure->draw_zone[i][j] = figure->fig_char;
				// if (((i <=  figure->Ytl && i + 1 >= figure->Ytl) && (j >= figure->Xtl && j <= figure->Xbr)))
				// 	figure->draw_zone[i][j] = figure->fig_char;
				// if (((i <=  figure->Ybr && i + 1 >= figure->Ybr) && (j >= figure->Xtl && j <= figure->Xbr)))
				// 	figure->draw_zone[i][j] = figure->fig_char;
				
// A pixel with a top left corner with a distance bigger or equal than 1 from the border of a rectangle is not part of an empty rectangle 
// A pixel with a top left corner with a distance lower than 1 from the border of a rectangle is part of an empty rectangle.
				// if (j - figure->Xtl < 1 && )
				
			}
		}
	}
}

int	get_figure(FILE *file, t_figure *figure)
{
	int	ret;

	ret = fscanf(file, " %c %f %f %f %f %c", &figure->r_char, &figure->Xtl, &figure->Ytl, &figure->width, &figure->heigth, &figure->fig_char);
	if (ret != 6)
		return (ft_perror(NULL, "Error: Operation file corrupted\n", 1));
	while (ret == 6)
	{
		if (figure->width <= 0 || figure->heigth <= 0)
			return (ft_perror(NULL, "Error: Operation file corrupted\n", 1));
		if (figure->r_char != 'r' && figure->r_char != 'R')
			return (ft_perror(NULL, "Error: Operation file corrupted\n", 1));
		figure->Xbr = figure->Xtl + figure->width;
		figure->Ybr = figure->Ytl + figure->heigth;
		put_figure_on_draw_zone(figure);
		ret = fscanf(file, " %c %f %f %f %f %c", &figure->r_char, &figure->Xtl, &figure->Ytl, &figure->width, &figure->heigth, &figure->fig_char);
		if (ret != 6 && ret != -1)
			return (ft_perror(NULL, "Error: Operation file corrupted\n", 1));
	}
	return (0);
}

int	main(int ac, char *av[])
{
	FILE *file;
	t_zone zone;
	t_figure figure;

	(void)av;
	if (ac != 2)
		return (ft_perror(NULL, "Error: argument\n", 1));
	file = fopen(av[1], "r");
	if (!file)
		return (ft_perror(NULL, "Error: Operation file corrupted\n", 1));
	if (get_zone(file, &zone, &figure) || get_figure(file, &figure))
		return (1);
	print_draw_zone(&figure);
	if (file)
		fclose(file);
	ft_free(&figure);
	return (0);
}