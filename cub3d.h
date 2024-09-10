/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:20:47 by susajid           #+#    #+#             */
/*   Updated: 2024/09/10 14:59:11 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include "mlx.h"

# define SPEED 8

// general events
enum
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17
};

// key events
enum
{
	KEY_ESC = 53,

	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,

	KEY_LEFT = 123,
	KEY_RIGHT = 124
};

typedef struct s_coord
{
	double	x;
	double	y;
	double	a;
	double	dx;
	double	dy;
}	t_coord;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*buf;
	int		bpp;
	int		l_len;
	int		endian;

	t_coord	player;
}	t_display;

int		mlx_setup(t_display *display);
int		render_display(t_display *display);
int		key_hook(int key, t_display *display);
void	pixel_put_image(t_display *display, int x, int y, int color);
void	clear_display(t_display *display);
void	draw_line(t_display *display, int x0, int y0, int x1, int y1, int color);
void	draw_3d_rays(t_display *display);
void	draw_player(t_display *display);
void	draw_square(t_display *display, int x, int y, int size, int color);
void	draw_2d_map(t_display *display);
int		update_xy(t_display *display, double new_x, double new_y);

#endif
