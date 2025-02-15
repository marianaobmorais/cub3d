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

void render_minimap(char **map, t_cub *data, int player_x, int player_y, int map_width, int map_height)
{
	int start_x = player_x - 9;
	int start_y = player_y - 7;
	int end_x = player_x + 9;
	int end_y = player_y + 7;


	if (start_x < 0)
	{
		end_x -= start_x;
		start_x = 0;
	}
	if (start_y < 0)
	{
		end_y -= start_y;
		start_y = 0;
	}
	if (end_x >= map_width)
	{
		start_x -= (end_x - map_width + 1);
		if (start_x < 0)
			start_x = 0;
		end_x = map_width - 1;
	}
	if (end_y >= map_height)
	{
		start_y -= (end_y - map_height + 1);
		if (start_y < 0)
			start_y = 0;
		end_y = map_height - 1;
	}

	int y = start_y;
	while (y <= end_y)
	{
		int x = start_x;
		while (x <= end_x)
		{
			// if (map[y] == NULL || x >= (int ) ft_strlen(map[y]))
			// 	continue;
			if (map[y][x] == '1')
				ft_put_square(data->minimap, x - start_x, y - start_y, GRAY);
			else if (map[y][x] == '0')
				ft_put_square(data->minimap, x - start_x, y - start_y, YELLOW);
			else
				ft_put_square(data->minimap, x - start_x, y - start_y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	ft_put_square(data->minimap, player_x - start_x, player_y - start_y, HOT_PINK);
}


void	ft_render_minimap(t_cub *cub)
{
	int	player_x;
	int	player_y;
	int	width;
	int	height;

	height = 0;
	while (cub->map->matrix[height])
		height++;
	player_x = cub->map->player_pos_x;
	player_y = cub->map->player_pos_y;
	width = (int) ft_strlen(cub->map->matrix[player_y]);
	ft_bg_minimap(cub, MINI_HEIGHT, MINI_WIDTH, 0x00FFFFFF);
	render_minimap(cub->map->matrix, cub, player_x, player_y, width, height);
}
