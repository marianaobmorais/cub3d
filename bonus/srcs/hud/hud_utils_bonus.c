/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:52:37 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/02 19:21:49 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

// void	ft_door(t_cub *cub, t_image *source, int pos_x, int pos_y)
// {
// 	//test
// 	int	source_color;
// 	int	blend;
// 	int default_color;
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < source->height)
// 	{
// 		x = 0;
// 		while (x < source->width)
// 		{
// 			source_color = ft_get_pixel_color(source, x, y, cub);
// 			if (source_color == 0x00FFFF) //color to ignore
// 			{
// 				default_color = ft_get_pixel_color(cub->image, x + pos_x, y +
//	 pos_y, cub);
// 				blend = ft_blendcolors(default_color, 0x00FFF0, 0.5);
// 				ft_put_pixel(cub->image, x + pos_x, y + pos_y, blend);
// 			}
// 			else
// 				ft_put_pixel(cub->image, x + pos_x, y + pos_y, source_color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

/**
 * @brief Updates the current position of a point along a line.
 *
 * This function modifies the coordinates of `tile` according to Bresenham's 
 * line algorithm, adjusting the error term to determine the next step.
 *
 * @param line A pointer to the line structure containing distance and error.
 * @param tile A pointer to the current point being processed.
 */
static void	setting_line(t_line *line, t_ipoint *tile)
{
	line->e2 = line->err * 2;
	if (line->e2 > -line->dist.y)
	{
		line->err -= line->dist.y;
		tile->y += line->dir.x;
	}
	if (line->e2 < line->dist.x)
	{
		line->err += line->dist.x;
		tile->x += line->dir.y;
	}
}

/**
 * @brief Draws a blended line between two points on the image.
 *
 * This function implements Bresenham's line algorithm to draw a line from 
 * `tile` to `hit`, blending the given `color` with the background color at 
 * each pixel.
 *
 * @param cub  A pointer to the main game structure.
 * @param tile The starting point of the line.
 * @param hit  The ending point of the line.
 * @param color The color to blend into the line.
 */
void	ft_draw_line(t_cub *cub, t_ipoint tile, t_ipoint hit, int color)
{
	t_line		line;
	int			blend;
	int			default_color;

	line.dist.y = abs(hit.x - tile.x);
	line.dist.x = abs(hit.y - tile.y);
	line.err = line.dist.x - line.dist.y;
	if (tile.y < hit.y)
		line.dir.x = 1;
	else
		line.dir.x = -1;
	if (tile.x < hit.x)
		line.dir.y = 1;
	else
		line.dir.y = -1;
	while (tile.y != hit.y || tile.x != hit.x)
	{
		default_color = ft_get_pixel_color(cub->image, tile.y, tile.x, cub);
		blend = ft_blendcolors(default_color, color, 0.9);
		ft_put_pixel(cub->image, tile.y, tile.x, blend);
		setting_line(&line, &tile);
	}
}

/**
 * @brief Converts a hexadecimal color to an RGB array.
 *
 * This function takes a color in hexadecimal format and extracts the 
 * individual red, green, and blue components. The RGB values are stored 
 * in the provided array, with each component represented as an unsigned 
 * char (0-255).
 *
 * @param hex The color in hexadecimal format (0xRRGGBB).
 * @param rgb The array where the RGB components will be stored.
 *             `rgb[0]` will contain the red component, `rgb[1]` 
 *             will contain the green component, and `rgb[2]` 
 *             will contain the blue component.
 */
void	ft_hextoarray(int hex, unsigned char *rgb)
{
	rgb[0] = (hex >> 16) & 0xFF;
	rgb[1] = (hex >> 8) & 0xFF;
	rgb[2] = hex & 0xFF;
}

/**
 * @brief Blends two colors based on a given alpha value.
 *
 * This function blends two colors using a specified alpha value, where `alpha`
 * controls the weight of the first color in the blend. The function calculates 
 * the RGB values for the blended color by mixing the components of the two 
 * colors according to the alpha value, and then returns the resulting color 
 * in hexadecimal format.
 *
 * @param color1 The first color to blend, represented in hexadecimal.
 * @param color2 The second color to blend, represented in hexadecimal.
 * @param alpha The alpha value controlling the blending ratio, ranging from 
 *              0.0 (fully `color2`) to 1.0 (fully `color1`).
 *
 * @return The resulting blended color in hexadecimal format.
 */
int	ft_blendcolors(int color1, int color2, float alpha)
{
	unsigned char	rgb1[3];
	unsigned char	rgb2[3];
	unsigned char	blended[3];

	if (alpha < 0.0)
		alpha = 0.0;
	if (alpha > 1.0)
		alpha = 1.0;
	ft_hextoarray(color1, rgb1);
	ft_hextoarray(color2, rgb2);
	blended[0] = (unsigned char)((rgb1[0] * alpha) + (rgb2[0] * (1 - alpha)));
	blended[1] = (unsigned char)((rgb1[1] * alpha) + (rgb2[1] * (1 - alpha)));
	blended[2] = (unsigned char)((rgb1[2] * alpha) + (rgb2[2] * (1 - alpha)));
	return (ft_arraytohex(blended));
}
