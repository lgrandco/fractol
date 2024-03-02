/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:00:15 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/02 14:24:09 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + y * data->line_length + x * 4;
	*(unsigned int *)dst = color;
}

int	create_trgb(const int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	linear_interpolate(const int *color1, const int *color2, double ratio)
{
	if (ratio < 0)
		return (0);
	return (create_trgb((int []){ratio * (color2[0] - color1[0]) + color1[0],
			(color2[1] - color1[1]) * ratio + color1[1], (color2[2] - color1[2])
			* ratio + color1[2]}));
}

double	distance(double x1, double y1, double x2, double y2)
{
	double	square_difference_x;
	double	square_difference_y;
	double	sum;
	double	value;

	square_difference_x = (x2 - x1) * (x2 - x1);
	square_difference_y = (y2 - y1) * (y2 - y1);
	sum = square_difference_x + square_difference_y;
	value = sqrt(sum);
	return (value);
}

void	fractol_init(t_vars *vars, char **av)
{
	vars->zoom = 1;
	vars->shift_val = 0;
	vars->pal = 0;
	vars->shift_bool = 1;
	vars->c.x = -.385;
	vars->c.y = -.6;
	vars->julia = 0;
	vars->mandel = 0;
	vars->ship = 0;
	if (av[2])
	{
		vars->c.x = ft_atof(av[2]);
		vars->c.y = ft_atof(av[3]);
	}
	vars->move_x = 0;
	vars->move_y = 0;
	vars->max_it = 50;
	if (!ft_strcmp(av[1], "julia"))
		vars->julia = 1;
	else if (!ft_strcmp(av[1], "mandelbrot"))
		vars->mandel = 1;
	else
		vars->ship = 1;
}

const int	g_palettes[6][5][3] = {{{0, 7, 100}, {32, 107, 203}, {237, 255,
	255}, {255, 170, 0}, {0, 2, 0}}, {{20, 0, 0}, {255, 20, 0}, {255, 200,
	0}, {255, 20, 0}, {20, 0, 0}}, {{189, 232, 247}, {140, 212, 233}, {38,
	195, 228}, {61, 152, 213}, {20, 117, 187}}, {{254, 237, 176}, {242, 149,
	103}, {207, 68, 86}, {131, 28, 99}, {47, 15, 62}}, {{255, 193, 0}, {255,
	154, 0}, {255, 116, 0}, {255, 77, 0}, {255, 0, 0}}, {{1, 31, 75}, {3,
	57, 108}, {0, 91, 150}, {100, 151, 177}, {179, 205, 224}}};
