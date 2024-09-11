#include "cub3d.h"

// int		mapX = 8;
// int		mapY = 8;

// int		map[] = {
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 0, 1, 0, 0, 0, 0, 1,
// 	1, 0, 1, 0, 0, 0, 0, 1,
// 	1, 0, 1, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 1, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 1,
// 	1, 1, 1, 1, 1, 1, 1, 1
// };

int	main(int argc, char **argv)
{
	t_display	display;

	init_info(&display);
	parse_input(argc, argv, &display);
	mlx_setup(&display);
	render_display(&display);
	mlx_loop(display.mlx);
	free_exit(NULL, &display, 0);
}

void	init_info(t_display *display)
{
	display->n_image = NULL;
	display->e_image = NULL;
	display->s_image = NULL;
	display->w_image = NULL;
	display->map = NULL;
	display->c = -1;
	display->f = -1;
	display->player.x = -1;
	display->player.y = -1;
	display->player.a = -1;
}

int	mlx_setup(t_display *display)
{
	display->mlx = mlx_init();
	display->win = NULL;
	display->img = NULL;
	if (!display->mlx)
		free_exit(NULL, display, 1); // error message
	display->win = mlx_new_window(display->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!display->win)
		free_exit(NULL, display, 2); // error message
	display->img = mlx_new_image(display->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!display->img)
		free_exit(NULL, display, 3); // error message
	display->buf = mlx_get_data_addr(display->img, &display->bpp, &display->l_len, &display->endian);
	mlx_hook(display->win, ON_DESTROY, 0, (int (*)())quit_display, display);
	mlx_hook(display->win, ON_KEYDOWN, 0, key_hook, display);
	return (0);
}

void	quit_display(t_display *display)
{
	free_exit(NULL, display, 0);
}

int	render_display(t_display *display)
{
	mlx_clear_window(display->mlx, display->win);
	clear_display(display);
	draw_2d_map(display);
	draw_3d_rays(display);
	draw_player(display);
	mlx_put_image_to_window(display->mlx, display->win, display->img, 0, 0);
	return (0);
}

void	clear_display(t_display *display)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			pixel_put_image(display, i, j, 0x4C4C4C);
			j++;
		}
		i++;
	}
}

int	key_hook(int key, t_display *display)
{
	if (key == KEY_ESC)
		quit_display(display);
	if (key == KEY_LEFT)
	{
		display->player.a = normalize_angle(display->player.a + 5);
		display->player.dx = cos(deg_to_rad(display->player.a));
		display->player.dy = -sin(deg_to_rad(display->player.a));
	}
	if (key == KEY_RIGHT)
	{
		display->player.a = normalize_angle(display->player.a - 5);
		display->player.dx = cos(deg_to_rad(display->player.a));
		display->player.dy = -sin(deg_to_rad(display->player.a));
	}
	if (key == KEY_W
		&& update_xy(display,
			display->player.x + display->player.dx * SPEED,
			display->player.y + display->player.dy * SPEED))
		return (1);
	if (key == KEY_S
		&& update_xy(display,
			display->player.x - display->player.dx * SPEED,
			display->player.y - display->player.dy * SPEED))
		return (1);
	if (key == KEY_A
		&& update_xy(display,
			display->player.x + display->player.dy * SPEED,
			display->player.y - display->player.dx * SPEED))
		return (1);
	if (key == KEY_D
		&& update_xy(display,
			display->player.x - display->player.dy * SPEED,
			display->player.y + display->player.dx * SPEED))
		return (1);
	render_display(display);
	return (0);
}

int	update_xy(t_display *display, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x / CUBE_SIZE;
	map_y = (int)new_y / CUBE_SIZE;
	if (map_x >= 0 && map_y >= 0
		&& map_y < display->map_height
		&& map_x < (int)ft_strlen(display->map[map_y])
		&& (display->map[map_y][map_x] == '0'
		|| ft_strchr("NESW", display->map[map_y][map_x])))
	{
		display->player.x = new_x;
		display->player.y = new_y;
		return (0);
	}
	return (1);
}

void	draw_2d_map(t_display *display)
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int	color;

	y = 0;
	while (y < display->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(display->map[y]))
		{
			if (display->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			xo = x * CUBE_SIZE;
			yo = y * CUBE_SIZE;
			draw_square(display, xo + 1, yo + 1, CUBE_SIZE - 1, color);
			x++;
		}
		y++;
	}
}

void	draw_3d_rays(t_display *display)
{
	t_coord	ray;
	int		r;
	double	temp_x;
	double	temp_y;
	double	dist_v;
	double	dist_h;

	int		line_height;
	int		line_offset;

	ray.a = normalize_angle(display->player.a + FOV / 2.0);
	r = 0;
	while (r < WIN_WIDTH)
	{
		dist_v = vertical_line_check(display->player, display->map, display->map_height, &ray);
		temp_x = ray.x;
		temp_y = ray.y;

		dist_h = horizontal_line_check(display->player, display->map, display->map_height, &ray);
		if (dist_v < dist_h)
		{
			ray.x = temp_x;
			ray.y = temp_y;
			dist_h = dist_v;
		}
		// draw_line(display, display->player.x, display->player.y, ray.x, ray.y, 0xFF0000);

		dist_h = dist_h * cos(deg_to_rad(normalize_angle(display->player.a - ray.a)));
		line_height = CUBE_SIZE * WIN_HEIGHT / dist_h;
		if (line_height >= WIN_HEIGHT)
			line_height = WIN_HEIGHT - 1;
		line_offset = WIN_HEIGHT / 2 - line_height / 2;
		draw_line(display, r, line_offset, r, line_offset + line_height, 0x00FF00);
		
		ray.a = normalize_angle(ray.a - (double)FOV / WIN_WIDTH);
		r++;
	}
}

double	horizontal_line_check(t_coord player, char **map, int map_height, t_coord *ray)
{
	double trig_ra = 1.0 / tan(deg_to_rad(ray->a));
	ray->x = player.x;
	ray->y = player.y;
	if (sin(deg_to_rad(ray->a)) > 0.001)
	{
		ray->y = (int)player.y / CUBE_SIZE * CUBE_SIZE - 0.0001;
		ray->dy = -CUBE_SIZE;
	}
	else if (sin(deg_to_rad(ray->a)) < -0.001)
	{
		ray->y = (int)player.y / CUBE_SIZE * CUBE_SIZE + CUBE_SIZE;
		ray->dy = CUBE_SIZE;
	}
	else
		return (INFINITY);
	ray->x = (player.y - ray->y) * trig_ra + player.x;
	ray->dx = -ray->dy * trig_ra;
	return (calc_dist(player, map, map_height, ray));
}

double	vertical_line_check(t_coord player, char **map, int map_height, t_coord *ray)
{
	double trig_ra = tan(deg_to_rad(ray->a));
	ray->x = player.x;
	ray->y = player.y;
	if(cos(deg_to_rad(ray->a)) > 0.001)
	{
		ray->x = (int)player.x / CUBE_SIZE * CUBE_SIZE + CUBE_SIZE;
		ray->dx = CUBE_SIZE;
	}
	else if (cos(deg_to_rad(ray->a)) < -0.001)
	{
		ray->x = (int)player.x / CUBE_SIZE * CUBE_SIZE - 0.0001;
		ray->dx = -CUBE_SIZE;
	}
	else
		return (INFINITY);
	ray->y = (player.x - ray->x) * trig_ra + player.y;
	ray->dy = -ray->dx * trig_ra;
	return (calc_dist(player, map, map_height, ray));
}

double	calc_dist(t_coord player, char **map, int map_height, t_coord *ray)
{
	int	map_x;
	int	map_y;

	while (1)
	{
		map_x = (int)ray->x / CUBE_SIZE;
		map_y = (int)ray->y / CUBE_SIZE;
		if (map_x < 0 || map_y < 0
			|| map_y >= map_height
			|| map_x >= (int)ft_strlen(map[map_y]))
			break ;
		if (map[map_y][map_x] == '1')
			return (cos(deg_to_rad(ray->a)) * (ray->x - player.x)
				- sin(deg_to_rad(ray->a)) * (ray->y - player.y));
		ray->x += ray->dx;
		ray->y += ray->dy;
	}
	return (INFINITY);
}

void	draw_player(t_display *display)
{
	int color = 0xFFFF00;
	draw_square(display, display->player.x - 4, display->player.y - 4, 8, color);
	draw_line(display, display->player.x, display->player.y, display->player.x + display->player.dx * 20, display->player.y + display->player.dy * 20, color);
}

void	draw_line(t_display *display, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
		pixel_put_image(display, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;       
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void	draw_square(t_display *display, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			pixel_put_image(display, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	pixel_put_image(t_display *display, int x, int y, int color)
{
	char	*dst;

	dst = display->buf + (y * display->l_len + x * (display->bpp / 8));
	*(unsigned int*)dst = color;
}

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	normalize_angle(double angle)
{
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}
