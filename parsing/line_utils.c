/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:53:38 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/13 10:36:26 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_player(t_display *display, int i, int j)
{
	if (display->player.a >= 0)
		free_exit("Only one player allowed", display, 1);
	display->player.x = j * CUBE_SIZE + CUBE_SIZE / 2.0 - 1;
	display->player.y = i * CUBE_SIZE + CUBE_SIZE / 2.0 - 1;
	if (display->map[i][j] == 'N')
		display->player.a = 90;
	else if (display->map[i][j] == 'E')
		display->player.a = 0;
	if (display->map[i][j] == 'S')
		display->player.a = 270;
	if (display->map[i][j] == 'W')
		display->player.a = 180;
	update_player_angle(&display->player, display->player.a);
}

int	well_surrounded(t_display *display, int i, int j)
{
	if (j < (int)ft_strlen(display->map[i]) - 1
		&& !ft_strchr("1 ", display->map[i][j + 1]))
		return (0);
	if (j > 0 && !ft_strchr("1 ", display->map[i][j - 1]))
		return (0);
	if (i > 0 && j < (int)ft_strlen(display->map[i - 1])
		&& !ft_strchr("1 ", display->map[i - 1][j]))
		return (0);
	if (display->map[i + 1] && j < (int)ft_strlen(display->map[i + 1])
		&& !ft_strchr("1 ", display->map[i + 1][j]))
		return (0);
	return (1);
}

int	is_edge(int i, int j, t_display *display)
{
	if ((i == 0 || i == display->map_height - 1
			|| j == 0 || j == (int)ft_strlen(display->map[i]) - 1))
		return (1);
	return (0);
}

int	is_wall(int i, int j, t_display *display)
{
	if (((i > 0 && j >= (int)ft_strlen(display->map[i - 1]))
			|| (i < display->map_height - 1
				&& j >= (int)ft_strlen(display->map[i + 1]))))
		return (1);
	return (0);
}

int	valid_line(t_display *display, int i)
{
	int	j;

	j = 0;
	while (display->map[i][j])
	{
		if (ft_strchr("NESW", display->map[i][j]))
			store_player(display, i, j);
		if (is_edge(i, j, display) && !ft_strchr("1 ", display->map[i][j]))
			return (0);
		else if (display->map[i][j] == ' ' && !well_surrounded(display, i, j))
			return (0);
		else if (is_wall(i, j, display) && !ft_strchr("1 ", display->map[i][j]))
			return (0);
		else if (!ft_strchr("10 NESW", display->map[i][j]))
			return (0);
		j++;
	}
	return (1);
}
