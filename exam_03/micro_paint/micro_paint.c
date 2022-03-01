/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:28:06 by rgelin            #+#    #+#             */
/*   Updated: 2022/03/01 17:30:57 by rgelin           ###   ########.fr       */
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

void	put_figure_on_draw_zone(t_figure *figure)
{
	int	i;
	int	j;
	
	i = -1;
	while (figure->draw_zone[++i])
	{
		j = -1;
		while (figure->draw_zone[i][++j])
		{
			if ((figure->Xtl <= (float)j && (float)j <= figure->Xbr) && (figure->Ytl <= (float)i && (float)i <= figure->Ybr))
			{
				if (figure->r_char == 'R')
					figure->draw_zone[i][j] = figure->fig_char;
				if (figure->r_char == 'r')
				{
					if (((float)j - figure->Xtl < (float)1 // left border
						|| (float)i - figure->Ytl < (float)1 // top border
						|| figure->Xbr - (float)j < (float)1 // rigth border
						|| figure->Ybr - (float)i < (float)1)) // bottom border
					figure->draw_zone[i][j] = figure->fig_char;
				}
			}
		}
	}
}

int	get_figure(FILE *file, t_figure *figure)
{
	int	ret;

	ret = fscanf(file, " %c %f %f %f %f %c", &figure->r_char, &figure->Xtl, &figure->Ytl, &figure->width, &figure->heigth, &figure->fig_char);
	if (ret != 6 && ret != -1)
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
