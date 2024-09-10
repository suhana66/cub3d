#include "cub3d.h"

int		mapX = 8;
int		mapY = 8;
int		mapS = 64;

int		map[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

int	main(void)
{
	t_display	display;

	display.exit_code = mlx_setup(&display);
	if (display.exit_code)
		quit_display(&display);
	display.player.x = 300;
	display.player.y = 300;
	display.player.a = 0;
	display.player.dx = cos(deg_to_rad(display.player.a));
	display.player.dy = -sin(deg_to_rad(display.player.a));
	render_display(&display);
	mlx_loop(display.mlx);
	return (0);
}

int	mlx_setup(t_display *display)
{
	display->mlx = mlx_init();
	display->win = NULL;
	display->img = NULL;
	if (!display->mlx)
		return (1); // error message
	display->win = mlx_new_window(display->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!display->win)
		return (2); // error message
	display->img = mlx_new_image(display->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!display->img)
		return (3); // error message
	display->buf = mlx_get_data_addr(display->img, &display->bpp, &display->l_len, &display->endian);
	mlx_hook(display->win, ON_DESTROY, 0, (int (*)())quit_display, display);
	mlx_hook(display->win, ON_KEYDOWN, 0, key_hook, display);
	return (0);
}

void	quit_display(t_display *display)
{
	if (!display)
		return ;
	if (display->img)
		mlx_destroy_image(display->mlx, display->img);
	if (display->win)
		mlx_destroy_window(display->mlx, display->win);
	free(display->mlx);
	exit(display->exit_code);
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
	if (if_in_map(new_x, new_y))
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
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			if (map[y * mapX + x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			xo = x * mapS;
			yo = y * mapS;
			draw_square(display, xo + 1, yo + 1, mapS - 1, color);
			x++;
		}
		y++;
	}
}

void	draw_3d_rays(t_display *display)
{
	int	r;

	double	vx;
	double	vy;
	double	disV;
	double	disH;

	t_coord		ray;

	ray.a = normalize_angle(display->player.a + 30);
	r = 0;
	while (r < 480)
	{
		disV = vertical_line_check(&display->player, &ray);
		vx = ray.x;
		vy = ray.y;

		disH = horizontal_line_check(&display->player, &ray);
		if (disV < disH)
		{
			ray.x = vx;
			ray.y = vy;
			disH = disV;
		}
		draw_line(display, display->player.x, display->player.y, ray.x, ray.y, 0xFF0000);

		int	ca = normalize_angle(display->player.a - ray.a);
		disH = disH * cos(deg_to_rad(ca));
		int	lineH = mapS * WIN_HEIGHT / disH;
		if (lineH >= WIN_HEIGHT)
			lineH = WIN_HEIGHT - 1;
		int	lineOff = (WIN_HEIGHT>>1) - (lineH>>1);

		draw_line(display, r + 530, lineOff, r + 530, lineOff + lineH, 0x00FF00);
		ray.a = normalize_angle(ray.a - 60.0 / 480.0);
		r++;
	}
}

double	horizontal_line_check(t_coord *player, t_coord *ray)
{
	// horizontal line check
	double Tan = 1.0 / tan(deg_to_rad(ray->a));
	ray->x = player->x;
	ray->y = player->y;
	if (sin(deg_to_rad(ray->a)) > 0.001)
	{
		ray->y = (((int)player->y>>6)<<6) - 0.0001;
		ray->dy = -64;
	}
	else if (sin(deg_to_rad(ray->a)) < -0.001)
	{
		ray->y = (((int)player->y>>6)<<6) + 64;
		ray->dy = 64;
	}
	else
		return (INFINITY);
	ray->x = (player->y - ray->y) * Tan + player->x;
	ray->dx = -ray->dy * Tan;
	return (calc_dist(player, ray));
}

double	vertical_line_check(t_coord *player, t_coord *ray)
{
	double Tan = tan(deg_to_rad(ray->a));
	ray->x = player->x;
	ray->y = player->y;
	if(cos(deg_to_rad(ray->a)) > 0.001)
	{
		ray->x = (((int)player->x>>6)<<6) + 64;
		ray->dx = 64;
	}
	else if (cos(deg_to_rad(ray->a)) < -0.001)
	{
		ray->x = (((int)player->x>>6)<<6) - 0.0001;
		ray->dx = -64;
	}
	else
		return (INFINITY);
	ray->y = (player->x - ray->x) * Tan + player->y;
	ray->dy = -ray->dx * Tan;
	return (calc_dist(player, ray));
}

double	calc_dist(t_coord *player, t_coord *ray)
{
	int map_x = (int)ray->x>>6;
	int map_y = (int)ray->y>>6;
	int map_pos = map_y * mapX + map_x;
	while(map_pos >= 0 && map_pos < mapX * mapY)
	{
		if (map[map_pos] == 1)
			return (cos(deg_to_rad(ray->a)) * (ray->x - player->x)
				- sin(deg_to_rad(ray->a)) * (ray->y - player->y));
		ray->x += ray->dx;
		ray->y += ray->dy;
		map_x = (int)ray->x>>6;
		map_y = (int)ray->y>>6;
		map_pos = map_y * mapX + map_x;
	}
	return (INFINITY);
}

int	if_wall(double x, double y)
{
	int	map_x;
	int	map_y;
	int	map_pos;

	map_x = (int)x>>6;
	map_y = (int)y>>6;
	map_pos = map_y * mapX + map_x;
	if (map_pos >= 0 && map_pos < mapX * mapY && map[map_pos] == 1)
		return (1);
	return (0);
}

int	if_in_map(double x, double y)
{
	int	map_x;
	int	map_y;
	int	map_pos;

	map_x = (int)x>>6;
	map_y = (int)y>>6;
	map_pos = map_y * mapX + map_x;
	if (map_pos >= 0 && map_pos < mapX * mapY && map[map_pos] == 0)
		return (1);
	return (0);
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
