/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:26:03 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/11 16:32:36 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	display->n_xpm.image = mlx_xpm_file_to_image(display->mlx, display->n_image,
			&display->n_xpm.w, &display->n_xpm.h);
	display->e_xpm.image = mlx_xpm_file_to_image(display->mlx, display->e_image,
			&display->e_xpm.w, &display->e_xpm.h);
	display->w_xpm.image = mlx_xpm_file_to_image(display->mlx, display->w_image,
			&display->w_xpm.w, &display->w_xpm.h);
	display->s_xpm.image = mlx_xpm_file_to_image(display->mlx, display->s_image,
			&display->s_xpm.w, &display->s_xpm.h);
	if (!display->n_xpm.image || !display->e_xpm.image
		|| !display->w_xpm.image || !display->s_xpm.image)
		return (0);
	display->n_xpm.buff = mlx_get_data_addr(display->n_xpm.image,
			&display->n_xpm.bpp, &display->n_xpm.l_len, &display->n_xpm.endian);
	display->e_xpm.buff = mlx_get_data_addr(display->e_xpm.image,
			&display->e_xpm.bpp, &display->e_xpm.l_len, &display->e_xpm.endian);
	display->w_xpm.buff = mlx_get_data_addr(display->w_xpm.image,
			&display->w_xpm.bpp, &display->w_xpm.l_len, &display->w_xpm.endian);
	display->s_xpm.buff = mlx_get_data_addr(display->s_xpm.image,
			&display->s_xpm.bpp, &display->s_xpm.l_len, &display->s_xpm.endian);
	return (1);
}
