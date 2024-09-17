/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaisal <mafaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:28:32 by mafaisal          #+#    #+#             */
/*   Updated: 2024/09/17 11:49:10 by mafaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_clear(char *str)
{
	free(str);
	str = NULL;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free_clear(array[i++]);
	free(array);
	array = NULL;
}

void	destroy_images(t_display *display)
{
	if (display->img.image)
		mlx_destroy_image(display->mlx, display->img.image);
	if (display->n_xpm.image)
		mlx_destroy_image(display->mlx, display->n_xpm.image);
	if (display->e_xpm.image)
		mlx_destroy_image(display->mlx, display->e_xpm.image);
	if (display->w_xpm.image)
		mlx_destroy_image(display->mlx, display->w_xpm.image);
	if (display->s_xpm.image)
		mlx_destroy_image(display->mlx, display->s_xpm.image);
	
}
void	free_exit(char *str, t_display *display, int exit_code)
{
	if (str && exit_code)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(str, 2);
	}
	if (!display)
		exit(exit_code);
	if (display->map)
		free_array(display->map);
	if (display->n_image)
		free_clear(display->n_image);
	if (display->e_image)
		free_clear(display->e_image);
	if (display->w_image)
		free_clear(display->w_image);
	if (display->s_image)
		free_clear(display->s_image);
	destroy_images(display);
	if (display->win)
		mlx_destroy_window(display->mlx, display->win);
	free(display->mlx);
	exit(exit_code);
}
