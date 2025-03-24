/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:57 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/24 17:19:53 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Paints a horizontal line in the background.
 *
 * This function fills a single horizontal line (row) of pixels in the image 
 * with the specified color.
 *
 * @param img Pointer to the image structure containing the buffer.
 * @param y The y-coordinate of the row to paint.
 * @param color The color value to fill the row with.
 */
static void	ft_paint_bg(t_image *img, int y, int color)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ft_put_pixel(img, x, y, color);
		x++;
	}
}

/**
 * @brief Renders the background by filling the ceiling and floor colors.
 *
 * This function iterates through the image's height, painting the top half 
 * with the ceiling color and the bottom half with the floor color.
 *
 * @param img Pointer to the image structure.
 * @param ceiling_color The color value for the ceiling.
 * @param floor_color The color value for the floor.
 */
static void	ft_render_bg(t_image *img, int ceiling_color, int floor_color)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y <= HEIGHT / 2)
			ft_paint_bg(img, y, ceiling_color);
		else
			ft_paint_bg(img, y, floor_color);
		y++;
	}
}

/**
 * @brief Handles the rendering of the game frame.
 *
 * This function updates the background, renders walls, and displays the final
 * image in the game window.
 *
 * @param cub Pointer to the main game structure.
 * @return Always returns 0.
 */
int	ft_handle_img(t_cub *cub)
{
	ft_render_bg(cub->image, cub->map->ceiling_hex, cub->map->floor_hex);
	ft_render_walls(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->image->img_ptr, 0, 0);
	return (0);
}
