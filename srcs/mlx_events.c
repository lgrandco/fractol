/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:58:32 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/02 18:31:52 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	t_point	point;

	point.x = (x - WIN_WIDTH / 2) / (double)WIN_WIDTH * 5 / vars->zoom
		+ vars->move_x;
	point.y = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * 5 / vars->zoom
		+ vars->move_y;
	if (button == 4)
	{
		if (vars->shift_bool)
			vars->shift_val++;
		vars->zoom *= 1.1;
	}
	else if (button == 5)
		vars->zoom /= 1.1;
	vars->move_x = -((x - WIN_WIDTH / 2) / (double)WIN_WIDTH * 5 / vars->zoom
			- point.x);
	vars->move_y = -((y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * 5 / vars->zoom
			- point.y);
	ft_printf("zoom: %u.%d\n", (long)vars->zoom, (int)(fmod(vars->zoom, 1)
			* 100));
	create_img(vars);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		destroy_exit_event(vars);
	if (keycode == XK_Up)
		vars->move_y -= .25 / vars->zoom;
	else if (keycode == XK_Down)
		vars->move_y += .25 / vars->zoom;
	else if (keycode == XK_Left)
		vars->move_x -= .25 / vars->zoom;
	else if (keycode == XK_Right)
		vars->move_x += .25 / vars->zoom;
	else if (keycode == XK_n)
		vars->pal = (vars->pal + 1) % 6;
	else if (keycode == XK_equal && ft_printf("max iterations: %d\n",
			(int)vars->max_it + 25))
		vars->max_it += 25;
	else if (keycode == XK_minus && ft_printf("max iterations: %d\n",
			(int)vars->max_it - 25))
		vars->max_it -= 25;
	else if (keycode == XK_s)
		vars->shift_bool = !vars->shift_bool;
	create_img(vars);
	return (0);
}

int	motion(int x, int y, t_vars *vars)
{
	static int	old_x = -1;
	static int	old_y = -1;

	if ((old_x != -1 && distance(x, y, old_x, old_y) < 3.5) || !vars->julia)
		return (0);
	old_x = x;
	old_y = y;
	vars->c.x = (x - WIN_WIDTH / 2) / (double)WIN_WIDTH * 5 / vars->zoom
		+ vars->move_x;
	vars->c.y = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * 5 / vars->zoom
		+ vars->move_y;
	ft_printf("coords: (%d.%d %d.%d)\n", (int)vars->c.x, (int)(fmod(vars->c.x,
				1) * 100), (int)vars->c.y, (int)(fmod(vars->c.y, 1) * 100));
	create_img(vars);
	return (0);
}

int	destroy_exit_event(t_vars *vars)
{
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}
