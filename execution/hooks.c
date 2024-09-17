/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:11:48 by susajid           #+#    #+#             */
/*   Updated: 2024/09/17 15:23:24 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit_display(t_display *display)
{
	free_exit(NULL, display, 0);
	return (0);
}

int	key_hook(int key, t_display *display)
{
	if (key == KEY_ESC)
		quit_display(display);
	if (key == KEY_LEFT)
		update_player_angle(&display->player, display->player.a + 5);
	if (key == KEY_RIGHT)
		update_player_angle(&display->player, display->player.a - 5);
	if (key == KEY_W && update_xy(display,
			display->player.x + display->player.dx * SPEED,
			display->player.y + display->player.dy * SPEED))
		return (1);
	if (key == KEY_S && update_xy(display,
			display->player.x - display->player.dx * SPEED,
			display->player.y - display->player.dy * SPEED))
		return (1);
	if (key == KEY_A && update_xy(display,
			display->player.x + display->player.dy * SPEED,
			display->player.y - display->player.dx * SPEED))
		return (1);
	if (key == KEY_D && update_xy(display,
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
	int	i;
	int	j;

	i = -PLAYER_SIZE / 2;
	while (i <= PLAYER_SIZE / 2)
	{
		j = -PLAYER_SIZE / 2;
		while (j <= PLAYER_SIZE / 2)
		{
			map_x = (int)(new_x + i) / CUBE_SIZE;
			map_y = (int)(new_y + j) / CUBE_SIZE;
			if (map_x < 0 || map_y < 0 || map_y >= display->map_height
				|| map_x >= (int)ft_strlen(display->map[map_y])
				|| (display->map[map_y][map_x] != '0'
				&& !ft_strchr("NESW", display->map[map_y][map_x])))
				return (1);
			j += PLAYER_SIZE / 2;
		}
		i += PLAYER_SIZE / 2;
	}
	display->player.x = new_x;
	display->player.y = new_y;
	return (0);
}

void	update_player_angle(t_coord *player, double new_angle)
{
	player->a = normalize_angle(new_angle);
	player->dx = cos(deg_to_rad(player->a));
	player->dy = -sin(deg_to_rad(player->a));
}
