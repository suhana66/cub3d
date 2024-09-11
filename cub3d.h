/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:20:47 by susajid           #+#    #+#             */
/*   Updated: 2024/09/11 10:22:34 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

# include <stdlib.h>
# include <math.h>
# include "mlx.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 512
# define WIN_TITLE "cub3d"

# define CUBE_SIZE 64
# define FOV 60
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
	int		c;
	int		f;
	char	**map;
	int		map_height;

	char	*n_image;
	char	*e_image;
	char	*w_image;
	char	*s_image;

	void	*n_xpm;
	void	*e_xpm;
	void	*w_xpm;
	void	*s_xpm;

}	t_display;

void	init_info(t_display *display);
int		mlx_setup(t_display *display);
void	quit_display(t_display *display);
int		render_display(t_display *display);
void	clear_display(t_display *display);
int		key_hook(int key, t_display *display);
int		update_xy(t_display *display, double new_x, double new_y);
void	draw_minimap(t_display *display);
void	draw_3d_rays(t_display *display);
double	horizontal_line_check(t_coord player, char **map, int map_height, t_coord *ray);
double	vertical_line_check(t_coord player, char **map, int map_height, t_coord *ray);
double	calc_dist(t_coord player, char **map, int map_height, t_coord *ray);
void	draw_line(t_display *display, int x0, int y0, int x1, int y1, int color);
void	draw_square(t_display *display, int x, int y, int size, int color);
void	pixel_put_image(t_display *display, int x, int y, int color);
double	deg_to_rad(double degrees);
double	normalize_angle(double angle);

// void	color_to_ascii(int *color, t_info *info, char *str);
void	save_color(char *str, t_display *display, int *error);

char	*custom_trim(char const *s1, char const *set, int side);

// void	store_player(t_info *info, int i, int j);
void	set_dx_dy(double angle, double *dx_res, double *dy_res);
// int		well_surrounded(t_info *info, int i, int j);
// int		is_edge(int i, int j, t_info *info);
// int		is_wall(int i, int j, t_info *info);
int		valid_line(t_display *display, int i);

void	save_map(char **map, t_display *display, char **file_content);
void	validate_map(t_display *display);

void	parse_input(int argc, char **argv, t_display *display);
// char	**store_info(char *filename, int lines_count);
// int		count_lines(int fd);
char	**read_file(char *file_name);

// bool	complete_elements(t_info *info);
// void	save_element(char *str, t_info *info, char **file_content);
// void	print_info(t_info *info);
void	store_validate(char **file_content, t_display *display);

// int		isoutlimit(long num, char c);
int		str_to_int(const char *str, int *error);

void	save_texture(char *str, t_display *display);
// bool	open_textures(t_display *display);

void	free_clear(char *str);
void	free_array(char **array);
void	free_exit(char *str, t_display *display, int exit_code);

#endif
