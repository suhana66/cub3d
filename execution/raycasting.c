/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:24:39 by susajid           #+#    #+#             */
/*   Updated: 2024/09/15 13:25:51 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d_rays(t_display *display)
{
	t_coord	xpm;
	t_image	cur_img;
	t_point	img_pt;
	int		line_height;
	int		line_offset;

	xpm.a = normalize_angle(display->player.a + FOV / 2.0);
	img_pt.x = 0;
	while (img_pt.x < WIN_WIDTH)
	{
		line_height = get_wall_height(display, xpm.a, &xpm.x, &cur_img);
		line_offset = WIN_HEIGHT / 2 - line_height / 2;
		xpm.y = 0;
		xpm.dy = (double)cur_img.h / line_height;
		img_pt.y = line_offset;
		while (img_pt.y - line_offset < line_height)
		{
			pixel_put_image(&display->img, img_pt,
				get_color(&cur_img, (t_point){xpm.x, xpm.y}));
			xpm.y += xpm.dy;
			img_pt.y++;
		}
		xpm.a = normalize_angle(xpm.a - (double)FOV / WIN_WIDTH);
		img_pt.x++;
	}
}

double	get_wall_height(t_display *display, double ray_angle, double *xpm_x,
			t_image *cur_img)
{
	t_coord	ray;
	double	v_y;
	double	dist_v;
	double	dist_h;

	ray.a = ray_angle;
	dist_v = v_line_check(display, &ray);
	v_y = ray.y;
	dist_h = h_line_check(display, &ray);
	if (dist_v <= dist_h)
	{
		*cur_img = display->e_xpm;
		if (cos(deg_to_rad(ray_angle)) < -0.001)
			*cur_img = display->w_xpm;
		*xpm_x = (double)((int)v_y % CUBE_SIZE) / CUBE_SIZE * cur_img->w;
	}
	else
	{
		*cur_img = display->n_xpm;
		if (sin(deg_to_rad(ray_angle)) < -0.001)
			*cur_img = display->s_xpm;
		*xpm_x = (double)((int)ray.x % CUBE_SIZE) / CUBE_SIZE * cur_img->w;
	}
	return (CUBE_SIZE * WIN_HEIGHT / (fmin(dist_h, dist_v)
			* cos(deg_to_rad(normalize_angle(display->player.a - ray_angle)))));
}

double	v_line_check(t_display *display, t_coord *ray)
{
	double	trig_ra;

	trig_ra = tan(deg_to_rad(ray->a));
	if (cos(deg_to_rad(ray->a)) > 0.001)
	{
		ray->x = (int)display->player.x / CUBE_SIZE * CUBE_SIZE + CUBE_SIZE;
		ray->dx = CUBE_SIZE;
	}
	else if (cos(deg_to_rad(ray->a)) < -0.001)
	{
		ray->x = (int)display->player.x / CUBE_SIZE * CUBE_SIZE - 0.0001;
		ray->dx = -CUBE_SIZE;
	}
	else
		return (INFINITY);
	ray->y = (display->player.x - ray->x) * trig_ra + display->player.y;
	ray->dy = -ray->dx * trig_ra;
	return (calc_dist(display->player, display->map, display->map_height, ray));
}

double	h_line_check(t_display *display, t_coord *ray)
{
	double	trig_ra;

	trig_ra = 1.0 / tan(deg_to_rad(ray->a));
	if (sin(deg_to_rad(ray->a)) > 0.001)
	{
		ray->y = (int)display->player.y / CUBE_SIZE * CUBE_SIZE - 0.0001;
		ray->dy = -CUBE_SIZE;
	}
	else if (sin(deg_to_rad(ray->a)) < -0.001)
	{
		ray->y = (int)display->player.y / CUBE_SIZE * CUBE_SIZE + CUBE_SIZE;
		ray->dy = CUBE_SIZE;
	}
	else
		return (INFINITY);
	ray->x = (display->player.y - ray->y) * trig_ra + display->player.x;
	ray->dx = -ray->dy * trig_ra;
	return (calc_dist(display->player, display->map, display->map_height, ray));
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
