#include <stdlib.h>
#include <math.h>
#include "mlx.h"

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

int		w_width;
int		w_height;

void	*mlx;
void	*win;
void	*img;

char	*buf;
int		bpp;
int		l_len;
int		endian;

double	py;
double	px;
double	pdx;
double	pdy;
double	pa;

int		display(void);
void	clear_display(void);
int		key_hook(int key);

void	draw_2d_map(void);
void	draw_3d_rays(void);
void	draw_player(void);

void	draw_line(int x0, int y0, int x1, int y1, int color);
void	draw_square(int x, int y, int size, int color);
void	pixel_put_image(int x, int y, int color);

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

int	main(void)
{
	w_width = 1024;
	w_height = 512;
	mlx = mlx_init();
	win = mlx_new_window(mlx, w_width, w_height, "Hello World");
	img = mlx_new_image(mlx, w_width, w_height);
	buf = mlx_get_data_addr(img, &bpp, &l_len, &endian);
	px = 300;
	py = 300;
	pa = 0;
	pdx = cos(deg_to_rad(pa));
	pdy = sin(deg_to_rad(pa));
	display();
	mlx_hook(win, ON_KEYDOWN, 0, key_hook, NULL);
	mlx_loop(mlx);
	(void)buf;
	return (0);
}

int	display(void)
{
	mlx_clear_window(mlx, win);
	clear_display();
	draw_2d_map();
	draw_3d_rays();
	draw_player();
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	return (0);
}

void	clear_display(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < w_width)
	{
		j = 0;
		while (j < w_height)
		{
			pixel_put_image(i, j, 0x4C4C4C);
			j++;
		}
		i++;
	}
}

int	key_hook(int key)
{
	if (key == KEY_A)
	{
		pa = normalize_angle(pa + 5);
		pdx = cos(deg_to_rad(pa));
		pdy = -sin(deg_to_rad(pa));
	}
	if (key == KEY_D)
	{
		pa = normalize_angle(pa - 5);
		pdx = cos(deg_to_rad(pa));
		pdy = -sin(deg_to_rad(pa));
	}
	if (key == KEY_W)
	{
		px += pdx;
		py += pdy;
	}
	if (key == KEY_S)
	{
		px -= pdx;
		py -= pdy;
	}
	display();
	return (0);
}

void	draw_2d_map(void)
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
			draw_square(xo + 1, yo + 1, mapS - 1, color);
			x++;
		}
		y++;
	}
}

void draw_3d_rays(void)
{
	int	r;
	int	mx;
	int	my;
	int	mp;
	int	dof;

	double	vx;
	double	vy;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	double	disV;
	double	disH;

	ra = normalize_angle(pa + 30);
	for(r=0;r<480;r++)
	{
		// vertical line check
		dof = 0;
		disV = 100000;
		double Tan = tan(deg_to_rad(ra));
		if(cos(deg_to_rad(ra)) > 0.001)
		{
			rx = (((int)px>>6)<<6) + 64;
			ry = (px - rx) * Tan + py;
			xo = 64;
			yo = -xo * Tan;
		}
		else if (cos(deg_to_rad(ra)) < -0.001)
		{
			rx = (((int)px>>6)<<6) - 0.0001;
			ry = (px - rx) * Tan + py;
			xo = -64;
			yo = -xo * Tan;
		}
		else
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while(dof<8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				dof = 8;
				disV = cos(deg_to_rad(ra)) * (rx - px) - sin(deg_to_rad(ra)) * (ry - py);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		vx = rx;
		vy = ry;

		// horizontal line check
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(deg_to_rad(ra)) > 0.001)
		{
			ry = (((int)py>>6)<<6) - 0.0001;
			rx = (py - ry) * Tan + px;
			yo = -64;
			xo = -yo * Tan;
		}
		else if (sin(deg_to_rad(ra)) < -0.001)
		{
			ry = (((int)py>>6)<<6) + 64;
			rx = (py - ry) * Tan + px;
			yo = 64;
			xo = -yo * Tan;
		}
		else
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				dof = 8;
				disH = cos(deg_to_rad(ra)) * (rx - px) - sin(deg_to_rad(ra)) * (ry - py);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disH = disV;
		}
		draw_line(px, py, rx, ry, 0xFF0000);

		int	ca = normalize_angle(pa - ra);
		disH = disH * cos(deg_to_rad(ca));
		int	lineH = mapS * w_height / disH;
		if (lineH > w_height)
			lineH = w_height;
		int	lineOff = (w_height>>1) - (lineH>>1);                                               //line offset

		draw_line(r + 530, lineOff, r + 530, lineOff + lineH, 0x00FF00);
		ra = normalize_angle(ra - 60.0 / 480.0);                                                        //go to next ray
	}
}

void	draw_player(void)
{
	int color = 0xFFFF00;
	draw_square(px - 4, py - 4, 8, color);
	draw_line(px, py, px + pdx * 20, py + pdy * 20, color);
}

void draw_line(int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
		pixel_put_image(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;       
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void	draw_square(int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			pixel_put_image(x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	pixel_put_image(int x, int y, int color)
{
	char	*dst;

	dst = buf + (y * l_len + x * (bpp / 8));
	*(unsigned int*)dst = color;
}
