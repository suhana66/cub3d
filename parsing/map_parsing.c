/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:26:33 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/10 21:27:18 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	save_map(char **map, t_display *display, char **file_content)
{
	int	i;

	i = 0;
	while (map[i] && !is_allspaces(map[i]))
		i++;
	display->map_height = i;
	while (map[i] && is_allspaces(map[i]))
		i++;
	if (map[i])
		(free_array(file_content), free_exit("Empty line", display, 1));
	display->map = malloc (sizeof(char *) * (display->map_height + 1));
	if (!display->map)
		(free_array(file_content), free_exit("Malloc error", display, 1));
	i = 0;
	while (i < display->map_height)
	{
		display->map[i] = custom_trim(map[i], " ", 2);
		i++;
	}
	display->map[i] = NULL;
}

void	validate_map(t_display *display)
{
	int	i;

	i = 0;
	while (display->map[i] && valid_line(display, i))
		i++;
	if (display->map[i])
		free_exit("Invalid map", display, 1);
	if (display->player.a == -1)
		free_exit("There should be at least one player", display, 1);
}
