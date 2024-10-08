/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaisal <mafaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:44:24 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/17 14:04:36 by mafaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	complete_elements(t_display *display)
{
	if (display->c >= 0 && display->f >= 0
		&& display->e_image && display->w_image
		&& display->s_image && display->n_image)
		return (1);
	return (0);
}

void	save_element(char *str, t_display *display, char **file_content)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	if (is_allspaces(str))
		return ;
	while (str[i] == ' ')
		i++;
	if (str[i]
		&& ((!ft_strncmp(str + i, "NO ", 3) && !display->n_image)
			|| (!ft_strncmp(str + i, "SO ", 3) && !display->s_image)
			|| (!ft_strncmp(str + i, "EA ", 3) && !display->e_image)
			|| (!ft_strncmp(str + i, "WE ", 3) && !display->w_image)))
		save_texture(str + i, display);
	else if (str[i]
		&& ((!ft_strncmp(str + i, "F ", 2) && display->f < 0)
			|| (!ft_strncmp(str + i, "C ", 2) && display->c < 0)))
		save_color(str + i, display, &error);
	else
		(free_array(file_content), free_exit("Invalid elements", display, 1));
	if (error)
		(free_array(file_content), free_exit("Invalid color format",
				display, 1));
}

void	print_info(t_display *display)
{
	int	i;

	printf("\n========Structure Elements=======\n\n");
	printf("c : %d,%d,%d\n", display->c >> 16,
		display->c >> 8 & 255, display->c & 255);
	printf("f : %d,%d,%d\n\n", display->f >> 16,
		display->f >> 8 & 255, display->f & 255);
	printf("NO: %s\n", display->n_image);
	printf("EA: %s\n", display->e_image);
	printf("SO: %s\n", display->s_image);
	printf("WE: %s\n\n", display->w_image);
	printf("Height: %d\n\n", display->map_height);
	i = 0;
	while (display->map[i])
		printf("%s\n", display->map[i++]);
	printf("player at %f %f with angle \'%f\n\n",
		display->player.x, display->player.y, display->player.a);
	printf("==================================\n\n");
}

void	store_validate(char **file_content, t_display *display)
{
	int	i;

	i = 0;
	while (file_content[i] && !complete_elements(display))
		save_element(file_content[i++], display, file_content);
	while (file_content[i] && is_allspaces(file_content[i]))
		i++;
	if (!file_content[i])
	{
		free_array(file_content);
		free_exit("Map doesn't exist", display, 1);
	}
	save_map(&file_content[i], display, file_content);
	free_array(file_content);
	validate_map(display);
	print_info(display);
}
