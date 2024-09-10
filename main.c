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
	int mx = (int)(new_x)>>6;
	int my = (int)(new_y)>>6;
	int mp = my * mapX + mx;
	if (mp > 0 && mp < mapX * mapY && map[mp] != 1)
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
	int	mx;
	int	my;
	int	mp;
	int	dof;

	double	vx;
	double	vy;
	double	disV;
	double	disH;

	t_coord		ray;

	ray.a = normalize_angle(display->player.a + 30);
	r = 0;
	while (r < 480)
	{
		// vertical line check
		dof = 0;
		disV = 100000;
		double Tan = tan(deg_to_rad(ray.a));
		if(cos(deg_to_rad(ray.a)) > 0.001)
		{
			ray.x = (((int)display->player.x>>6)<<6) + 64;
			ray.y = (display->player.x - ray.x) * Tan + display->player.y;
			ray.dx = 64;
			ray.dy = -ray.dx * Tan;
		}
		else if (cos(deg_to_rad(ray.a)) < -0.001)
		{
			ray.x = (((int)display->player.x>>6)<<6) - 0.0001;
			ray.y = (display->player.x - ray.x) * Tan + display->player.y;
			ray.dx = -64;
			ray.dy = -ray.dx * Tan;
		}
		else
		{
			ray.x = display->player.x;
			ray.y = display->player.y;
			dof = 8;
		}
		while(dof<8)
		{
			mx = (int)(ray.x)>>6;
			my = (int)(ray.y)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				dof = 8;
				disV = cos(deg_to_rad(ray.a)) * (ray.x - display->player.x) - sin(deg_to_rad(ray.a)) * (ray.y - display->player.y);
			}
			else
			{
				ray.x += ray.dx;
				ray.y += ray.dy;
				dof += 1;
			}
		}
		vx = ray.x;
		vy = ray.y;

		// horizontal line check
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(deg_to_rad(ray.a)) > 0.001)
		{
			ray.y = (((int)display->player.y>>6)<<6) - 0.0001;
			ray.x = (display->player.y - ray.y) * Tan + display->player.x;
			ray.dy = -64;
			ray.dx = -ray.dy * Tan;
		}
		else if (sin(deg_to_rad(ray.a)) < -0.001)
		{
			ray.y = (((int)display->player.y>>6)<<6) + 64;
			ray.x = (display->player.y - ray.y) * Tan + display->player.x;
			ray.dy = 64;
			ray.dx = -ray.dy * Tan;
		}
		else
		{
			ray.x = display->player.x;
			ray.y = display->player.y;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(ray.x)>>6;
			my = (int)(ray.y)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				dof = 8;
				disH = cos(deg_to_rad(ray.a)) * (ray.x - display->player.x) - sin(deg_to_rad(ray.a)) * (ray.y - display->player.y);
			}
			else
			{
				ray.x += ray.dx;
				ray.y += ray.dy;
				dof += 1;
			}
		}
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
