/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:22:28 by susajid           #+#    #+#             */
/*   Updated: 2024/09/17 15:01:33 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	normalize_angle(double angle)
{
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return (angle);
}

void	pixel_put_image(t_image *img, t_point pixel, int color)
{
	char	*dst;

	if (pixel.x < 0 || pixel.x >= WIN_WIDTH
		|| pixel.y < 0 || pixel.y >= WIN_HEIGHT)
		return ;
	dst = img->buff + (pixel.y * img->l_len + pixel.x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_image *image, t_point pixel)
{
	char	*dst;
	int		color;

	if (pixel.x < 0 || pixel.x > image->w || pixel.y > image->h)
		return (0);
	dst = image->buff + (pixel.y * image->l_len + pixel.x * (image->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
