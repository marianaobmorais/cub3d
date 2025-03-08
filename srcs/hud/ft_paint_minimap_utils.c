#include "../../includes/cub3d.h"

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
			if (i == 0 || i == size - 1 || j == 0 || j == size - 1 ||
				(i == 1 && (j == 1 || j == size - 2)) ||
				(i == size - 2 && (j == 1 || j == size - 2)))
			{
				offset = ((y + i) * img->line_len) + ((x + j) * (img->bpp / 8));
				*((unsigned int *)(offset + img->addr)) = color;
			}
			j++;
		}
		i++;
	}
}

void	ft_set_limit_x(t_cub *cub, int matrix_width)
{
	cub->hud->start_x = cub->map->player_squ_x - 8;
	cub->hud->end_x = cub->map->player_squ_x + 8;
	if (cub->hud->start_x < 0)
	{
		cub->hud->end_x -= cub->hud->start_x;
		cub->hud->start_x = 0;
	}
	if (cub->hud->end_x >= matrix_width)
	{
		cub->hud->start_x -= (cub->hud->end_x - matrix_width + 1);
		if (cub->hud->start_x < 0)
			cub->hud->start_x = 0;
		cub->hud->end_x = matrix_width - 1;
	}
}

void	ft_set_limit_y(t_cub *cub, int matrix_height)
{
	cub->hud->start_y = cub->map->player_squ_y - 5;
	cub->hud->end_y = cub->map->player_squ_y + 5;
	if (cub->hud->start_y < 0)
	{
		cub->hud->end_y -= cub->hud->start_y;
		cub->hud->start_y = 0;
	}
	if (cub->hud->end_y >= matrix_height)
	{
		cub->hud->start_y -= (cub->hud->end_y - matrix_height + 1);
		if (cub->hud->start_y < 0)
			cub->hud->start_y = 0;
		cub->hud->end_y = matrix_height - 1;
	}
}
