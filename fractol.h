/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:12:51 by leo               #+#    #+#             */
/*   Updated: 2023/12/13 19:03:42 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "mlx_int.h"
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_point
{
	double	x;
	double	y;
}			t_point;

typedef struct s_vars
{
	t_point	c;
	double	zoom;
	double	moveY;
	double	moveX;
	void	*mlx;
	void	*win;
	t_data	img;
	double	max_it;
}			t_vars;

#endif // !PIPEX_H
