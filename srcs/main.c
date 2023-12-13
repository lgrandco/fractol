/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 50023/11/29 02:23:49 by legrandc          #+#    #+#             */
/*   Updated: 2023/12/07 18:28:40 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"

void	img_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y)*data->line_length + x * 4;
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	iter(t_point point, t_point c, double max_it)
{
	int		i;
	t_point	new;

	i = 0;
	// ft_bzero(&point, 2);
	while (i++ < max_it)
	{
		if (point.x * point.x + point.y * point.y > 3.5)
		{
			// printf("%f (*) %f= %f\n", point.x, point.y, point.x * point.x
			// 	+ point.y * point.y);
			return (i);
		}
		new.x = point.x *point.x - point.y *point.y + c.x;
		new.y = 2 * point.x *point.y + c.y;
		point = new;
	}
	return (0);
}

void	create_img(t_vars *vars)
{
	t_point	point;
	double	iters;
	float	x;
	float	y;

	vars->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			point.y = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * 5 / vars->zoom
				+ vars->moveY;
			point.x = (x - WIN_WIDTH / 2) / (double)WIN_WIDTH * 5 / vars->zoom
				+ vars->moveX;
			iters = iter(point, vars->c, vars->max_it) / vars->max_it * 255;
			if (iters && iters < 127)
				iters = 127;
			if (iters)
				img_pixel_put(&vars->img, x, y, create_trgb(255, iters, 170,
						205));
			else
				img_pixel_put(&vars->img, x, y, create_trgb(0, 255, 255, 255));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img.img);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	printf("%d\n", button);
	printf("%f\n", vars->zoom);
	if (button == 4)
		vars->zoom *= 1.1;
	else if (button == 5)
		vars->zoom /= 1.1;
	create_img(vars);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == XK_Up)
		vars->moveY -= (0.25) / vars->zoom;
	else if (keycode == XK_Down)
		vars->moveY += (0.25) / vars->zoom;
	else if (keycode == XK_Left)
		vars->moveX -= (0.25) / vars->zoom;
	else if (keycode == XK_Right)
		vars->moveX += (0.25) / vars->zoom;
	printf("%f %f\n", vars->moveX, vars->moveY);
	create_img(vars);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.zoom = 1;
	printf("%f\n", vars.zoom);
	// vars.c.x = -.385;
	vars.c.x = .285;
	// vars.c.y = .6;
	vars.c.y = .01;
	vars.moveX = 0;
	vars.moveY = 0;
	vars.mlx = mlx_init();
	vars.max_it = 175;
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	create_img(&vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}
