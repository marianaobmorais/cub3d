/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:34:49 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/10 16:35:39 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

/**
 * @brief Retrieves the color value of a pixel from an image buffer.
 * 
 * This function extracts the color value of the pixel at the specified (w, h) 
 * coordinates in the given image. It ensures that the coordinates are within 
 * valid bounds. If the image is invalid or the coordinates are out of bounds, 
 * an error is handled, and the function returns 0.
 * 
 * @param source Pointer to the image structure containing pixel data.
 * @param w The x-coordinate of the pixel.
 * @param h The y-coordinate of the pixel.
 * @param cub Pointer to the main game structure, used for error handling.
 * @return The color value of the pixel as an unsigned integer.
 */
unsigned int	ft_get_pixel_color(t_image *source, int w, int h, t_cub *cub)
{
	char			*color;
	int				offset;
	unsigned int	color_value;

	if (!source || !source->addr || w < 0 || w > source->width
		|| h < 0 || h > source->height)
		return (ft_handle_error("ft_get_pixel_color", cub), 0);
	offset = (h * source->line_len + w * (source->bpp / 8));
	color = source->addr + offset;
	ft_memcpy(&color_value, color, sizeof(unsigned int));
	return (color_value);
}
