/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:23:04 by  legrandc         #+#    #+#             */
/*   Updated: 2024/02/23 14:54:18 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_vars	vars;

	if ((ac != 2 && ac != 4) || (ft_strcmp(ft_lower(av[1]), "julia")
			&& ft_strcmp(av[1], "mandelbrot") && ft_strcmp(av[1],
				"burning_ship")))
	{
		ft_printf(USAGE);
		return (0);
	}
	fractol_init(&vars, av);
	vars.mlx = mlx_init();
	if (!vars.mlx && ft_printf("Mlx error\n"))
		destroy_exit_event(&vars);
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	if (!vars.win && ft_printf("Mlx error\n"))
		destroy_exit_event(&vars);
	create_img(&vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, MotionNotify, Button1MotionMask, motion, &vars);
	mlx_hook(vars.win, DestroyNotify, NoEventMask, destroy_exit_event, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_loop(vars.mlx);
}
