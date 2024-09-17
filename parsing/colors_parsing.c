/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaisal <mafaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:25:35 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/17 13:44:50 by mafaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_to_ascii(int *color, t_display *display, char *str)
{
	if (*str == 'C')
	{
		display->c = 0;
		display->c |= color[0] << 16;
		display->c |= color[1] << 8;
		display->c |= color[2];
	}
	else if (*str == 'F')
	{
		display->f = 0;
		display->f |= color[0] << 16;
		display->f |= color[1] << 8;
		display->f |= color[2];
	}
}

void	save_color(char *str, t_display *display, int *error)
{
	int		color[3];
	int		end;
	char	*color_segment;
	char	*temp_str;
	int		i;

	temp_str = str + 2;
	while (*temp_str == ' ')
		temp_str++;
	i = 0;
	while (*temp_str && i < 3)
	{
		if (i > 0 && i < 3 && *temp_str == ',')
			temp_str++;
		end = 0;
		while (ft_isdigit(*(temp_str + end)))
			end++;
		color_segment = ft_substr(temp_str, 0, end);
		color[i++] = str_to_int(color_segment, error);
		free(color_segment);
		temp_str += end;
	}
	if (i == 3 && is_allspaces(temp_str))
		color_to_ascii(color, display, str);
}
