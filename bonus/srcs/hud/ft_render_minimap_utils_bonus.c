/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_minimap_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:11:23 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/02 20:59:15 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Draws a small square on the given image.
 *
 * This function renders a 5x5 pixel square at the specified position 
 * with the given color. The square is outlined using specific pixel 
 * placement logic to create a grid-like effect.
 *
 * @param img Pointer to the image where the square will be drawn.
 * @param x X-coordinate (scaled by square size).
 * @param y Y-coordinate (scaled by square size).
 * @param color Color of the square.
 */
void	ft_put_square(t_image *img, int x, int y, int color)
{
	int	offset;
	int	i;
	int	j;
	int	size;

	size = 5;
	i = 0;
	x *= size;
	y *= size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if ((i % 4 == 0) || (j % 4 == 0) || (i == size - 1)
				|| (j == size - 1))
			{
				offset = ((y + i) * img->line_len) + ((x + j) * (img->bpp / 8));
				*((unsigned int *)(offset + img->addr)) = color;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Sets the horizontal limits for the minimap view.
 *
 * This function defines the starting and ending X-coordinates for 
 * rendering the minimap, ensuring they remain within the matrix 
 * boundaries. Adjustments are made if the player's position is 
 * near the edges.
 *
 * @param cub Pointer to the main game structure.
 * @param matrix_height Total height of the map matrix.
 */
void	ft_set_limit_x(t_cub *cub, int matrix_height)
{
	cub->hud->start_x = cub->raycast->player_tile.x - 4;
	cub->hud->end_x = cub->raycast->player_tile.x + 4;
	if (cub->hud->start_x < 0)
	{
		cub->hud->end_x -= cub->hud->start_x;
		cub->hud->start_x = 0;
	}
	if (cub->hud->end_x >= matrix_height)
	{
		cub->hud->start_x -= (cub->hud->end_x - matrix_height + 1);
		if (cub->hud->start_x < 0)
			cub->hud->start_x = 0;
	}
}

/**
 * @brief Sets the vertical limits for the minimap view.
 *
 * This function defines the starting and ending Y-coordinates for 
 * rendering the minimap, ensuring they remain within the matrix 
 * boundaries. Adjustments are made if the player's position is 
 * near the edges.
 *
 * @param cub Pointer to the main game structure.
 * @param matrix_width Total width of the map matrix.
 */
void	ft_set_limit_y(t_cub *cub, int matrix_width)
{
	cub->hud->start_y = cub->raycast->player_tile.y - 8;
	cub->hud->end_y = cub->raycast->player_tile.y + 8;
	if (cub->hud->start_y < 0)
	{
		cub->hud->end_y -= cub->hud->start_y;
		cub->hud->start_y = 0;
	}
	if (cub->hud->end_y >= matrix_width)
	{
		cub->hud->start_y -= (cub->hud->end_y - matrix_width + 1);
		if (cub->hud->start_y < 0)
			cub->hud->start_y = 0;
	}
}

/**
 * @brief Renders a player icon onto the image at the specified position.
 *
 * This function draws a small square (3x3 pixels) representing the player 
 * at the given coordinates (x, y) on the specified image. The square is 
 * filled with the provided color. It is primarily used for visualizing the 
 * player's position on the screen or in other image buffers.
 *
 * @param img The image where the player icon will be drawn.
 * @param x The x-coordinate of the top-left corner of the player icon.
 * @param y The y-coordinate of the top-left corner of the player icon.
 * @param color The color used to fill the player icon (usually a single color)
 */
void	ft_put_player(t_image *img, int x, int y, int color)
{
	int	offset;
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 3;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			offset = ((y + i) * img->line_len) + ((x + j) * (img->bpp / 8));
			*((unsigned int *)(offset + img->addr)) = color;
			j++;
		}
		i++;
	}
}
