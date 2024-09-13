/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:24:39 by susajid           #+#    #+#             */
/*   Updated: 2024/09/13 11:35:36 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d_rays(t_display *display)
{
	t_coord	ray;
	int		r;
	double	v_y;
	double	dist_v;
	double	dist_h;

	t_image	cur_img;
	int		x_image;
	double	y_image;
	double	y_step;

	int		line_height;
	int		line_offset;

	int		i;

	ray.a = normalize_angle(display->player.a + FOV / 2.0);
	r = 0;
	while (r < WIN_WIDTH)
	{
		dist_v = v_line_check(display->player, display->map, display->map_height, &ray);
		v_y = ray.y;

		dist_h = h_line_check(display->player, display->map, display->map_height, &ray);
		cur_img = get_image(display, ray.a, dist_v, dist_h);
		if (dist_v < dist_h)
			x_image = (double)((int)v_y % CUBE_SIZE) / CUBE_SIZE * cur_img.w;
		else
			x_image = (double)((int)ray.x % CUBE_SIZE) / CUBE_SIZE * cur_img.w;
		y_image = 0;
		// draw_line(display, display->player.x, display->player.y, ray.x, ray.y, 0xFF0000);

		dist_h = fmin(dist_h, dist_v) * cos(deg_to_rad(normalize_angle(display->player.a - ray.a)));
		line_height = CUBE_SIZE * WIN_HEIGHT / dist_h;
		if (line_height > WIN_HEIGHT)
			line_height = WIN_HEIGHT;
		line_offset = WIN_HEIGHT / 2 - line_height / 2;

		y_step = (double)cur_img.h / line_height;
		i = 0;
		while (i < line_height)
		{
			pixel_put_image(&display->img, (t_point){r, line_offset + i},
				get_color(&cur_img, (t_point){x_image, y_image}));
			y_image += y_step;
			i++;
		}
		ray.a = normalize_angle(ray.a - (double)FOV / WIN_WIDTH);
		r++;
	}
}

t_image	get_image(t_display *display, double ray_angle, double dist_v, double dist_h)
{
	if (dist_v < dist_h)
	{
		if (cos(deg_to_rad(ray_angle)) < -0.001)
			return (display->w_xpm);
		else
			return (display->e_xpm);
	}
	else
	{
		if (sin(deg_to_rad(ray_angle)) > 0.001)
			return (display->n_xpm);
		else
			return(display->s_xpm);
	}
}

double	h_line_check(t_coord player, char **map, int map_height, t_coord *ray)
{
	double	trig_ra;

	trig_ra = 1.0 / tan(deg_to_rad(ray->a));
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

double	v_line_check(t_coord player, char **map, int map_height, t_coord *ray)
{
	double	trig_ra;

	trig_ra = tan(deg_to_rad(ray->a));
	ray->x = player.x;
	ray->y = player.y;
	if (cos(deg_to_rad(ray->a)) > 0.001)
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

