/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:26:03 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/10 20:34:32 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	save_texture(char *str, t_display *display)
{
	
	if (*str == 'N')
		display->n_image = ft_strtrim(str + 2, " ");
	else if (*str == 'S')
		display->s_image = ft_strtrim(str + 2, " ");
	else if (*str == 'E')
		display->e_image = ft_strtrim(str + 2, " ");
	else if (*str == 'W')
		display->w_image = ft_strtrim(str + 2, " ");
}

int	open_textures(t_display *display)
{
	int	w;
	int	h;

	display->n_xpm = mlx_xpm_file_to_image(display->mlx, display->n_image, &w, &h);
	display->e_xpm = mlx_xpm_file_to_image(display->mlx, display->e_image, &w, &h);
	display->w_xpm = mlx_xpm_file_to_image(display->mlx, display->w_image, &w, &h);
	display->s_xpm = mlx_xpm_file_to_image(display->mlx, display->s_image, &w, &h);
	if (!display->n_xpm || !display->e_xpm || !display->w_xpm || !display->s_xpm)
		return (0);
	return (1);
}