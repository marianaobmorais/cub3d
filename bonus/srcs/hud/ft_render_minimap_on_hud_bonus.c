#include "../../includes/cub3d_bonus.h"

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

void	ft_colorize_minimap(t_cub *cub, int map_width, int map_height)
{
	int	y;
	int	x;
	int	tile_pos_x;
	int	tile_pos_y;

	x = cub->hud->start_x;
	while (x < map_height && x <= cub->hud->end_x)
	{
		y = cub->hud->start_y;
		while (y < map_width -1 && y <= cub->hud->end_y)
		{
			tile_pos_y = (y - cub->hud->start_y) + 4;
			tile_pos_x = (x - cub->hud->start_x) + 9;
			if (x >= 0 && y >= 0 && cub->map->matrix[x][y] != '\0')
			{
				if (cub->map->matrix[x][y] == '1')
					ft_put_square(cub->image, tile_pos_y, tile_pos_x, BLACK);
				else if (cub->map->matrix[x][y] == '0')
					ft_put_square(cub->image, tile_pos_y, tile_pos_x, GRAY);
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
