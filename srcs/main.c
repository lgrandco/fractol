/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:23:49 by legrandc          #+#    #+#             */
/*   Updated: 2023/12/02 18:51:44 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

void	img_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y)*data->line_length + x * 4;
	*(unsigned int *)dst = color;
}
t_point	c = {-7, 0.27015};

int	iter(t_point point)
{
	int		i;
	t_point	new;

	i = 0;
	// ft_bzero(&point, 2);
	while (i++ < 2)
	{
		if (point.x * point.x + point.y * point.y > 4)
		{
			printf("%f (*) %f= %f\n", point.x, point.y, point.x * point.x
				+ point.y * point.y);
			return (1);
		}
		new.x = point.x *point.x - point.y *point.y + c.x;
		new.y = 2 * point.x *point.y + c.y;
		point.x = new.x;
		point.y = new.y;
	}
	return (0);
}

void	put_pixel(t_data *img, int x, int y)
{
	t_point	point;

	point.y = (y - WIN_HEIGHT / 2) / (double)WIN_HEIGHT * 5;
	point.x = (x - WIN_WIDTH / 2) / (double)WIN_WIDTH * 5;
	// printf("%f   %f\n", point.x, point.y);
	if (iter(point))
		img_pixel_put(img, x, y, 0xFFFFFFFF);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		x;
	int		y;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	printf("%d %d %d\n", img.line_length, img.bits_per_pixel, img.endian);
	img_pixel_put(&img, 0, 100, 0xFFFFFFFF);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
