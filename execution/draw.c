/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:18:17 by susajid           #+#    #+#             */
/*   Updated: 2024/09/11 16:31:45 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_image *img, char **map, t_coord player)
{
	int	i;
	int	j;
	int	scale;

	i = 0;
	scale = 16;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(img, j * scale, i * scale, scale, 0x515e48);
			else if (map[i][j] == '0' || ft_strchr("NSEW", map[i][j]))
				draw_square(img, j * scale, i * scale, scale, 0xacc29d);
			j++;
		}
		i++;
	}
	draw_square(img, player.x / 4 - scale / 4, player.y / 4 - scale / 4, scale / 2, 0xAA0000);
	draw_line(img, player.x / 4, player.y / 4, player.x / 4 + player.dx * scale, player.y / 4 + player.dy * scale, 0xAA0000);
}

void	draw_line(t_image *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		pixel_put_image(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_square(t_image *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			pixel_put_image(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	pixel_put_image(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->buff + (y * img->l_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_image *image, int x, int y)
{
	char	*dst;
	int		color;

	dst = image->buff + (y * image->l_len + x * (image->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
