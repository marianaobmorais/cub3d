#include "../../includes/cub3d.h"

void	ft_bg_minimap(t_cub *cub, int height, int width, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			//ft_put_pixel(cub->hud->img, x + 17, y + 39, color);
			ft_put_pixel(cub->image, x + 17, y + 39, color);
			x++;
		}
		y++;
	}
}

void	ft_colorize_minimap(t_cub *cub, int map_width, int map_height)
{
	int	y;
	int	x;
	int	pos_x = 3;
	int pos_y = 8;
	
	y = cub->hud->start_y;
	while (y < map_height && y <= cub->hud->end_y)
	{
		x = cub->hud->start_x;
		while (x < map_width -1 && x <= cub->hud->end_x)
		{
			if (y >= 0 && x >= 0 && cub->map->matrix[y][x] != '\0')
			{
				if (cub->map->matrix[y][x] == '1')
				{
					//ft_put_square(cub->hud->img, (x - cub->hud->start_x) + pos_x, (y - cub->hud->start_y) + pos_y, BLACK);
					ft_put_square(cub->image, (x - cub->hud->start_x) + pos_x, (y - cub->hud->start_y) + pos_y, BLACK);
				}
				else if (cub->map->matrix[y][x] == '0')
				{
					//ft_put_square(cub->hud->img, (x - cub->hud->start_x) + pos_x, (y - cub->hud->start_y) + pos_y, GRAY_2);
					ft_put_square(cub->image, (x - cub->hud->start_x) + pos_x, (y - cub->hud->start_y) + pos_y, GRAY_2);
				}
			}
			x++;
		}
		y++;
	}
	//ft_put_square(cub->hud->img, (cub->map->player_squ_x - cub->hud->start_x) + pos_x, (cub->map->player_squ_y - cub->hud->start_y) + pos_y, RED);
	ft_put_square(cub->image, (cub->map->player_squ_x - cub->hud->start_x) + pos_x, (cub->map->player_squ_y - cub->hud->start_y) + pos_y, RED);
}

void	ft_paint_minimap_on_hud(t_cub *cub)
{
	int	width;
	int	height;

	height = 0;
	while (cub->map->matrix[height])
		height++;
	width = (int) ft_strlen(cub->map->matrix[cub->map->player_squ_y]);
	ft_bg_minimap(cub, MINI_HEIGHT, MINI_WIDTH, GRAY_2);
	ft_set_limit_x(cub, width);
	ft_set_limit_y(cub, height);
	ft_colorize_minimap(cub, width, height);
}
