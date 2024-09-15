/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:18:17 by susajid           #+#    #+#             */
/*   Updated: 2024/09/15 12:19:36 by susajid          ###   ########.fr       */
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
				draw_square(img, (t_point){j * scale, i * scale},
					scale, 0x515e48);
			else if (map[i][j] == '0' || ft_strchr("NSEW", map[i][j]))
				draw_square(img, (t_point){j * scale, i * scale},
					scale, 0xacc29d);
			j++;
		}
		i++;
	}
	draw_square(img, (t_point){player.x / 4 - scale / 4,
		player.y / 4 - scale / 4}, scale / 2, 0xAA0000);
	draw_line(img, (t_point){player.x / 4, player.y / 4}, (t_point){player.x / 4
		+ player.dx * scale, player.y / 4 + player.dy * scale}, 0xAA0000);
}

/*
	BRESENHAM'S LINE DRAWING ALGORITHM
	=> The variables sx and sy denote
		the direction and magnitude of the x and y increment respectively.
	=> The variable err denotes the slope error
		i.e. the deviation from the ideal line's position.

	Initially, err = dx - dy
	2 * err > -dy
	=> 2 * (dx - dy) > -dy
	=> 2dx - 2dy > -dy
	=> 2dx - 2dy + dy > 0
	=> 2dx - dy > 0
	=> 2dx > dy
	=> dx / dy > 1 / 2
	This means that the slope error is greater than 0.5 in the x-direction.
	This can be thought as while 2 steps have been made in the y-direction,
		only 1 step in the x-direction; a step in the x-direction is overdue.
	Correspondingly, dy is subtracted from the error term
		as we are moving in the x-direction.

	Initially, err = dx - dy
	2 * err < dx
	=> 2 * (dx - dy) < dx
	=> 2dx - 2dy < dx
	=> dx - 2dy < 0
	=> dx < 2dy
	=> 1 / 2 < dy / dx
	=> dy / dx > 1 / 2
	This means that the slope error is greater than 0.5 in the y-direction.
	This can be thought as while 2 steps have been made in the x-direction,
		only 1 step in the y-direction; a step in the y-direction is overdue.
	Correspondingly, dx is added to the error term
		as we are moving in the y-direction.
*/
void	draw_line(t_image *img, t_point a, t_point b, int color)
{
	t_point	delta;
	t_point	step;
	int		err;
	int		e2;

	delta.x = abs(b.x - a.x);
	delta.y = abs(b.y - a.y);
	if (a.x < b.x)
		step.x = 1;
	else
		step.x = -1;
	if (a.y < b.y)
		step.y = 1;
	else
		step.y = -1;
	err = delta.x - delta.y;
	while (1)
	{
		pixel_put_image(img, a, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * err;
		(e2 > -delta.y) && (err -= delta.y, a.x += step.x);
		(e2 < delta.x) && (err += delta.x, a.y += step.y);
	}
}

void	draw_square(t_image *img, t_point start, int size, int color)
{
	t_point	temp;

	temp.x = start.x;
	while (temp.x - start.x < size)
	{
		temp.y = start.y;
		while (temp.y - start.y < size)
		{
			pixel_put_image(img, temp, color);
			temp.y++;
		}
		temp.x++;
	}
}

void	pixel_put_image(t_image *img, t_point pixel, int color)
{
	char	*dst;

	if (pixel.x < 0 || pixel.x >= WIN_WIDTH
		|| pixel.y < 0 || pixel.y >= WIN_HEIGHT)
		return ;
	dst = img->buff + (pixel.y * img->l_len + pixel.x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_image *image, t_point pixel)
{
	char	*dst;
	int		color;

	if (pixel.x < 0 || pixel.x > image->w || pixel.y > image->h)
		return (0);
	dst = image->buff + (pixel.y * image->l_len + pixel.x * (image->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
