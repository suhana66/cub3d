#include <stdlib.h>
#include <mlx.h>

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

int		display(void);
void	clear_display(void);
int		key_hook(int key);

void	draw_2d_map(void);
void	draw_player(void);

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
	mlx_loop_hook(mlx, display, NULL);
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
		px -= 5;
	if (key == KEY_D)
		px += 5;
	if (key == KEY_W)
		py -= 5;
	if (key == KEY_S)
		py += 5;
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
			// TODO
			x++;
		}
		y++;
	}
	(void)xo;
	(void)yo;
	(void)color;
}

void	draw_player(void)
{
	draw_square(px - 4, py - 4, 8, 0xFFFF00);
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
