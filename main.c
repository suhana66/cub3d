/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:08:14 by susajid           #+#    #+#             */
/*   Updated: 2024/09/15 16:32:15 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_display	display;

	init_info(&display);
	parse_input(argc, argv, &display);
	mlx_setup(&display);
	render_display(&display);
	mlx_loop(display.mlx);
	free_exit(NULL, &display, 0);
}

void	init_info(t_display *display)
{
	display->mlx = NULL;
	display->win = NULL;
	display->img.image = NULL;
	display->n_image = NULL;
	display->e_image = NULL;
	display->s_image = NULL;
	display->w_image = NULL;
	display->map = NULL;
	display->c = -1;
	display->f = -1;
	display->player.x = -1;
	display->player.y = -1;
	display->player.a = -1;
}

int	mlx_setup(t_display *display)
{
	display->mlx = mlx_init();
	if (!display->mlx)
		free_exit("Failed to initialize MLX", display, 1);
	display->win = mlx_new_window(display->mlx, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!display->win)
		free_exit("Failed to create window", display, 2);
	display->img.image = mlx_new_image(display->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!display->img.image)
		free_exit("Failed to create image", display, 3);
	display->img.buff = mlx_get_data_addr(display->img.image,
			&display->img.bpp, &display->img.l_len, &display->img.endian);
	mlx_hook(display->win, ON_DESTROY, 0, (int (*)())quit_display, display);
	mlx_hook(display->win, ON_KEYDOWN, 0, key_hook, display);
	if (!open_textures(display))
		free_exit("Failed to open textures", display, 4);
	return (0);
}

int	render_display(t_display *display)
{
	mlx_clear_window(display->mlx, display->win);
	set_background(&display->img, display->c, display->f);
	draw_3d_rays(display);
	draw_minimap(&display->img, display->map, display->player);
	mlx_put_image_to_window(display->mlx, display->win,
		display->img.image, 0, 0);
	return (0);
}

void	set_background(t_image *img, int ceiling, int floor)
{
	t_point	pixel;

	pixel.x = 0;
	while (pixel.x < WIN_WIDTH)
	{
		pixel.y = 0;
		while (pixel.y < WIN_HEIGHT)
		{
			if (pixel.y < WIN_HEIGHT / 2)
				pixel_put_image(img, pixel, ceiling);
			else
				pixel_put_image(img, pixel, floor);
			pixel.y++;
		}
		pixel.x++;
	}
}
