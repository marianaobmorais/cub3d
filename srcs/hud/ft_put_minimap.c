#include "../../includes/minimap.h"

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
			ft_put_pixel(cub->mini->img_minimap, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_colorize_minimap(t_cub *cub, int map_width, int map_height)
{
	int	y;
	int	x;
	
	y = cub->mini->start_y;
	while (y < map_height && y <= cub->mini->end_y)
	{
		x = cub->mini->start_x;
		while (x < map_width -1 && x <= cub->mini->end_x)
		{
			//printf("y[%d] -- x[%d]\n", y, x); //debug
			if (y >= 0 && x >= 0 && cub->map->matrix[y][x] != '\0')
			{
				if (cub->map->matrix[y][x] == '1')
				{
					//printf("y[%d] -- x[%d]\n", y, x); //debug
					ft_put_square(cub->mini->img_minimap, x - cub->mini->start_x, y - cub->mini->start_y, 0x000000);
				}
				else if (cub->map->matrix[y][x] == '0')
				{
					//printf("y[%d] -- x[%d]\n", y, x); //debug
					ft_put_square(cub->mini->img_minimap, x - cub->mini->start_x, y - cub->mini->start_y, 0xB1B1B3);
				}
				// else
				// 	ft_put_square(cub->minimap, x - cub->map->start_x, y - cub->map->start_y, HOT_PINK);
			}
			x++;
		}
		y++;
	}
	ft_put_square(cub->mini->img_minimap, cub->map->player_pos_x - cub->mini->start_x, \
		cub->map->player_pos_y - cub->mini->start_y, HOT_PINK);
}

void	ft_render_minimap(t_cub *cub)
{
	int	width;
	int	height;

	height = 0;
	while (cub->map->matrix[height])
		height++;
	width = (int) ft_strlen(cub->map->matrix[cub->map->player_pos_y]);
	ft_bg_minimap(cub, MINI_HEIGHT, MINI_WIDTH, 0xB1B1B3);
	ft_set_limit_x(cub, width);
	ft_set_limit_y(cub, height);
	ft_colorize_minimap(cub, width, height);
}


void	ft_put_minimap(t_cub *cub)
{
	if (cub->mini->img_minimap->img_ptr)
		mlx_destroy_image(cub->mlx, cub->mini->img_minimap->img_ptr);
	cub->mini->img_minimap->img_ptr = mlx_new_image(cub->mlx, \
		MINI_WIDTH, MINI_HEIGHT);
	if (!cub->mini->img_minimap->img_ptr)
		ft_handle_error("malloc: img->img_ptr", cub);
	cub->mini->img_minimap->bpp = 0;
	cub->mini->img_minimap->line_len = 0;
	cub->mini->img_minimap->endian = 0;
	cub->mini->img_minimap->addr = mlx_get_data_addr( \
		cub->mini->img_minimap->img_ptr,
		&cub->mini->img_minimap->bpp, &cub->mini->img_minimap->line_len, \
		&cub->mini->img_minimap->endian);
	if (!cub->mini->img_minimap->addr)
		ft_handle_error("malloc: img->addr", cub);
	ft_background(cub);
	ft_render_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, \
		cub->mini->img_minimap->img_ptr, 22, 44);
}

