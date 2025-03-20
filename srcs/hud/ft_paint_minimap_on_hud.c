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
			ft_put_pixel(cub->image, x + 20, y + 42, color);
			x++;
		}
		y++;
	}
}

void	ft_colorize_minimap(t_cub *cub, int map_width, int map_height)
{
	int	y;
	int	x;
	int	pos_x = 9;
	int pos_y = 4;
	int player_y = (cub->raycast->player_squ.y - cub->hud->start_y) + (pos_y);
	int player_x = (cub->raycast->player_squ.x - cub->hud->start_x) + (pos_x);
	
	
	x = cub->hud->start_x;
	while (x < map_height && x <= cub->hud->end_x)
	{
		y = cub->hud->start_y;
		while (y < map_width -1 && y <= cub->hud->end_y)
		{
			if (x >= 0 && y >= 0 && cub->map->matrix[x][y] != '\0')
			{
				if (cub->map->matrix[x][y] == '1')
				{
					//ft_put_square(cub->hud->img, (x - cub->hud->start_x) + pos_x, (y - cub->hud->start_y) + pos_y, BLACK);
					ft_put_square(cub->image, (y - cub->hud->start_y) + pos_y, (x - cub->hud->start_x) + pos_x, BLACK);
				}
				else if (cub->map->matrix[x][y] == '0')
				{
					//ft_put_square(cub->hud->img, (x - cub->hud->start_x) + pos_x, (y - cub->hud->start_y) + pos_y, GRAY_2);
					ft_put_square(cub->image, (y - cub->hud->start_y) + pos_y, (x - cub->hud->start_x) + pos_x, GRAY);
				}
			}
			y++;
		}
		x++;
	}
	//ft_put_square(cub->hud->img, (cub->map->player_squ_x - cub->hud->start_x) + pos_x, (cub->map->player_squ_y - cub->hud->start_y) + pos_y, RED);
	ft_put_player(cub->image, player_y, player_x, RED);
}

void	draw_line_minimap(t_cub *cub, int x1, int y1, int x2, int y2, int color)
{
	//test
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (x1 != x2 || y1 != y2)
	{
		ft_put_pixel(cub->image, x1, y1, color);
		int e2 = err * 2;
		if (e2 > -dy) { err -= dy; x1 += sx; }
		if (e2 < dx) { err += dx; y1 += sy; }
	}
}

void	ft_render_fov_minimap(t_cub *cub)
{
	//test
	int	i;
	int	map_x;
	int	map_y;
	int	player_x;
	int	player_y;

	i = 0;
	while (i < WIDTH)
	{
		map_x = cub->hud->ray_hits[i].x * MINIMAP_SCALE_X;
		map_y = cub->hud->ray_hits[i].y * MINIMAP_SCALE_Y;
		player_x = cub->raycast->player_squ.x * MINIMAP_SCALE_X;
		player_y = cub->raycast->player_squ.y * MINIMAP_SCALE_Y;
		draw_line_minimap(cub, player_x + 9, player_y + 4, map_x + 9, map_y + 4, RED);
		printf("line"); //debug
		i += 10;
	}
}

void	ft_paint_minimap_on_hud(t_cub *cub)
{
	// int	width;
	// int	height;

	// height = 0;
	// while (cub->map->matrix[height])
	// 	height++;
	// width = (int) ft_strlen(cub->map->matrix[cub->map->player_squ_y]);
	ft_bg_minimap(cub, MINI_HEIGHT, MINI_WIDTH, GRAY_2);
	ft_set_limit_x(cub, cub->map->height);
	ft_set_limit_y(cub, cub->map->width);
	ft_colorize_minimap(cub, cub->map->width, cub->map->height);
	//ft_render_fov_minimap(cub);
	
}
