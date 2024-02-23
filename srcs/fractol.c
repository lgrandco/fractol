/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:05:26 by legrandc          #+#    #+#             */
/*   Updated: 2024/02/23 15:00:33 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	iterate(t_vars *vars, t_point point, t_point c, double max_it)
{
	double	i;
	t_point	new;
	double	log_zn;
	double	nu;

	i = 0;
	while (i++ < max_it)
	{
		if (vars->ship)
		{
			point.x = fabs(point.x);
			point.y = fabs(point.y);
		}
		if (point.x * point.x + point.y * point.y > 64)
		{
			log_zn = log(point.x * point.x + point.y * point.y) / 2;
			nu = log(log_zn / log(2)) / log(2);
			return (i - nu);
		}
		new.x = point.x * point.x - point.y * point.y + c.x;
		new.y = 2 * point.x * point.y + c.y;
		point = new;
	}
	return (0);
}

void	color_img(t_vars *vars, int x, int y)
{
	double	iters;
	t_point	point;
	int		color1;
	int		color2;

	point.y = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * 5 / vars->zoom
		+ vars->moveY;
	point.x = (x - WIN_WIDTH / 2) / (double)WIN_WIDTH * 5 / vars->zoom
		+ vars->moveX;
	if (!vars->julia)
		vars->c = point;
	iters = iterate(vars, point, vars->c, vars->max_it);
	if (!iters)
		return ;
	while (iters < 0)
		iters += 5;
	iters += vars->shift_val;
	color1 = iters;
	color2 = iters + 1;
	img_pixel_put(&vars->img, x, y,
		linear_interpolate(g_palettes[vars->pal][color1 % 5],
			g_palettes[vars->pal][color2 % 5], fmod(iters, 1)));
}

void	create_img(t_vars *vars)
{
	double	y;
	double	x;

	vars->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!vars->img.img && ft_printf("Mlx error\n"))
		destroy_exit_event(vars);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color_img(vars, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img.img);
}
