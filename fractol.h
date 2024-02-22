/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:12:51 by leo               #+#    #+#             */
/*   Updated: 2024/02/22 13:08:58 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

extern const int	g_palettes[][5][3];

# define USAGE "Usage: ./fractol (julia | mandelbrot | burning_ship) [c.x c.y]\n"

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_vars
{
	int				shift_bool;
	size_t			shift_val;
	int				julia;
	int				mandel;
	int				ship;
	t_point			c;
	t_point			mouse_pos;
	double			zoom;
	double			moveY;
	double			moveX;
	void			*mlx;
	void			*win;
	t_data			img;
	double			max_it;
	int				pal;
}					t_vars;

/* FUNCTIONS */
void				fractol_init(t_vars *vars, char **av);
double				distance(double x1, double y1, double x2, double y2);
int					linear_interpolate(const int *color1, const int *color2,
						double ratio);
int					create_trgb(const int *rgb);
void				img_pixel_put(t_data *data, int x, int y, int color);
int					destroy_exit_event(t_vars *vars);
int					motion(int x, int y, t_vars *vars);
int					key_hook(int keycode, t_vars *vars);
int					mouse_hook(int button, int x, int y, t_vars *vars);
void				create_img(t_vars *vars);
void				color_img(t_vars *vars, int x, int y);
double				iterate(t_vars *vars, t_point point, t_point c,
						double max_it);

#endif // !PIPEX_H
