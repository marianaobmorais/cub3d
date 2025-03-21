/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:34:49 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/21 11:05:20 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Sets a pixel's color in an image buffer.
 *
 * This function calculates the memory offset for a pixel at coordinates
 * `(x, y)` within the given image and updates its color. The image structure
 * contains necessary metadata such as bytes per pixel (`bpp`), line length, and
 * the memory address of the image buffer.
 *
 * @param img Pointer to the image structure containing the buffer.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color value to assign to the pixel.
 */
void	ft_put_pixel(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = 0;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}

unsigned int	ft_get_pixel_color(t_image source, int w, int h)
{
	//add brief
	char	*color;
	int		offset;

	if (!source.addr || w < 0 || w >= source.width || h < 0 || h >= source.height)
		return (0);
	offset = (h * source.line_len + w * (source.bpp / 8));
	color = source.addr + offset;
	return (*(unsigned int *)color);
}
