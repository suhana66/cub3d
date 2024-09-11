/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:11:48 by susajid           #+#    #+#             */
/*   Updated: 2024/09/11 16:20:10 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	quit_display(t_display *display)
{
	free_exit(NULL, display, 0);
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
