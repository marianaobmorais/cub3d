#include "../../includes/cub3d.h"

// char	**ft_matrixdup(char **matrix, t_cub *cub)
// {
// 	int		i;
// 	char	**dup;

// 	i = 0;
// 	dup = NULL;
// 	while (matrix[i])
// 		i++;
// 	dup = (char **) malloc(i * sizeof(char *));
// 	if (!dup)
// 		ft_handle_error("malloc: matrixdup", cub);
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		dup[i] = ft_strdup(matrix[i]);
// 		i++;
// 	}
// 	dup[i] = NULL;
// 	return (dup);
// }

void	ft_put_square(t_image *img, int x, int y, int color)
{
	//add brief
	int	offset;
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 5;
	x *= size;
	y *= size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			offset = ((y + i) * img->line_len) + ((x  + j) * (img->bpp / 8));
			*((unsigned int *)(offset + img->addr)) = color;
			j++;
		}
		i++;
	}
}

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
			ft_put_pixel(cub->minimap, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_put_pixel_minimap(t_cub *cub, int start_x, int start_y, int end_x, int end_y)
{
	int	y;
	int	x;
	
	y = start_y;
	while (y <= end_y)
	{
		x = start_x;
		while (x <= end_x)
		{
			// if (map[y] == NULL || x >= (int ) ft_strlen(map[y]))
			// 	continue;
			if (cub->map->matrix[y][x] == '1')
				ft_put_square(cub->minimap, x - start_x, y - start_y, GRAY);
			else if (cub->map->matrix[y][x] == '0')
				ft_put_square(cub->minimap, x - start_x, y - start_y, YELLOW);
			else
				ft_put_square(cub->minimap, x - start_x, y - start_y, HOT_PINK);
			x++;
		}
		y++;
	}
	ft_put_square(cub->minimap, cub->map->player_pos_x - start_x, cub->map->player_pos_y - start_y, HOT_PINK);
}

void	ft_colorize_minimap(t_cub *cub, int map_width, int map_height)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = cub->map->player_pos_x - 9;
	start_y = cub->map->player_pos_y - 7;
	end_x = cub->map->player_pos_x + 9;
	end_y = cub->map->player_pos_y + 7;
	if (start_x < 0)
	{
		end_x -= start_x;
		start_x = 0;
	}
	if (end_x >= map_width)
	{
		start_x -= (end_x - map_width + 1);
		if (start_x < 0)
			start_x = 0;
		end_x = map_width - 1;
	}
	if (start_y < 0)
	{
		end_y -= start_y;
		start_y = 0;
	}
	if (end_y >= map_height)
	{
		start_y -= (end_y - map_height + 1);
		if (start_y < 0)
			start_y = 0;
		end_y = map_height - 1;
	}
	ft_put_pixel_minimap(cub, start_x, start_y, end_x, end_y);
}


void	ft_render_minimap(t_cub *cub)
{
	int	width;
	int	height;

	height = 0;
	while (cub->map->matrix[height])
		height++;
	width = (int) ft_strlen(cub->map->matrix[cub->map->player_pos_y]);
	ft_bg_minimap(cub, MINI_HEIGHT, MINI_WIDTH, HOT_PINK);
	ft_colorize_minimap(cub, width, height);
}

void	ft_put_minimap(t_cub *cub)
{
	if (cub->minimap->img_ptr)
		mlx_destroy_image(cub->mlx, cub->minimap->img_ptr);
	cub->minimap->img_ptr = mlx_new_image(cub->mlx, MINI_WIDTH, MINI_HEIGHT);
	if (!cub->minimap->img_ptr)
		ft_handle_error("malloc: img->img_ptr", cub);
	cub->minimap->bpp = 0;
	cub->minimap->line_len = 0;
	cub->minimap->endian = 0;
	cub->minimap->addr = mlx_get_data_addr(cub->minimap->img_ptr, \
		&cub->minimap->bpp, &cub->minimap->line_len, &cub->minimap->endian);
	if (!cub->minimap->addr)
		ft_handle_error("malloc: img->addr", cub);
	ft_render_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->minimap->img_ptr, 10, 10);
}
