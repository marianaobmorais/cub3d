/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_minimap_on_hud_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:11:58 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/10 20:55:33 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Renders a solid background color onto the main image.
 *
 * This function fills the area defined by the specified height and width 
 * with the given color, starting from a fixed position `(pos_x, pos_y)`. 
 * It loops through each pixel in the region and sets it to the provided 
 * color, creating a solid background effect.
 *
 * @param cub The main game structure containing the current image.
 * @param height The height of the area to be filled.
 * @param width The width of the area to be filled.
 * @param color The color to fill the background (in hexadecimal format).
 */
static void	ft_render_background(t_cub *cub, int height, int width, int color)
{
	int	y;
	int	x;
	int	pos_x;
	int	pos_y;

	y = 0;
	pos_x = 20;
	pos_y = 42;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			ft_put_pixel(cub->image, x + pos_x, y + pos_y, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Paints a tile on the map based on the type of tile in the matrix.
 *
 * This function checks the tile type in the map matrix and paints it 
 * accordingly. Different tile types are assigned different colors for 
 * rendering: walls, doors, and player or empty tiles are handled 
 * with specific rendering functions.
 *
 * @param cub The game structure containing the map and image to render to.
 * @param tile The coordinates of the tile to paint.
 * @param x The x-coordinate in the map matrix.
 * @param y The y-coordinate in the map matrix.
 */
static void	ft_paint_tile(t_cub *cub, t_ipoint tile, int x, int y)
{
	if (cub->map->matrix[x][y] == '1')
		ft_put_square(cub->image, tile.y, tile.x, BLACK);
	else if (cub->map->matrix[x][y] == 'D')
		ft_put_square(cub->image, tile.y, tile.x, ORANGE);
	else if (cub->map->matrix[x][y] == 'X')
		ft_put_x(cub->image, tile.y, tile.x, BLUE);
	else if (ft_is_player(cub->map->matrix[x][y])
		|| cub->map->matrix[x][y] == '0')
		ft_put_square(cub->image, tile.y, tile.x, GRAY);
}

/**
 * @brief Colors the minimap based on the current map data.
 *
 * This function iterates through the map matrix and renders each tile 
 * onto the minimap area. The tiles are color-coded based on their content:
 * walls ('1') are colored black, and player positions, empty spaces ('0'), 
 * and other specific tiles ('P') are colored gray. The rendering is done 
 * starting from a specific area of the screen defined by the minimap 
 * start and end coordinates.
 *
 * @param cub The main game structure containing the map data and image.
 * @param map_width The width of the map.
 * @param map_height The height of the map.
 */
static void	ft_colorize_minimap(t_cub *cub, int map_width, int map_height)
{
	int			y;
	int			x;
	t_ipoint	tile;

	x = cub->hud->start_x;
	while (x < map_height && x <= cub->hud->end_x)
	{
		y = cub->hud->start_y;
		while (y < map_width && y <= cub->hud->end_y)
		{
			tile.y = (y - cub->hud->start_y) + 4;
			tile.x = (x - cub->hud->start_x) + 9;
			if (x >= 0 && y >= 0 && cub->map->matrix[x][y] != '\0')
			{
				ft_paint_tile(cub, tile, x, y);
			}
			y++;
		}
		x++;
	}
}

/**
* @brief Renders the minimap on the HUD.
*
* This function draws the minimap background, sets the map limits, 
* and applies colors based on the map's dimensions. The field of 
* view rendering is currently commented out.
*
* @param cub Pointer to the main game structure.
*/
void	ft_render_minimap_on_hud(t_cub *cub)
{
	ft_render_background(cub, MINI_HEIGHT, MINI_WIDTH, GRAY_2);
	ft_set_limit_x(cub, cub->map->height);
	ft_set_limit_y(cub, cub->map->width);
	ft_colorize_minimap(cub, cub->map->width, cub->map->height);
	ft_render_fov_minimap(cub);
}
