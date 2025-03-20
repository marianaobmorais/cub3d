#include "../../includes/cub3d.h"

void	ft_put_square(t_image *img, int x, int y, int color)
{
	int	offset;
	int	i, j;
	int	size = 5;

	x *= size;
	y *= size;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if ((i % 4 == 0) || (j % 4 == 0) || (i == size - 1) || (j == size - 1))
			{
				offset = ((y + i) * img->line_len) + ((x + j) * (img->bpp / 8));
				*((unsigned int *)(offset + img->addr)) = color;
			}
		}
	}
}

void	ft_set_limit_x(t_cub *cub, int matrix_height)
{
	cub->hud->start_x = cub->raycast->player_squ.x - 4;
	cub->hud->end_x = cub->raycast->player_squ.x + 4;
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
		//cub->hud->end_x = matrix_height - 1;
	}
}

void	ft_set_limit_y(t_cub *cub, int matrix_width)
{
	cub->hud->start_y = cub->raycast->player_squ.y - 8;
	cub->hud->end_y = cub->raycast->player_squ.y + 8;
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
		//cub->hud->end_y = matrix_width - 1;
	}
}

void	ft_put_player(t_image *img, int x, int y, int color)
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
			offset = ((y + i) * img->line_len) + ((x + j) * (img->bpp / 8));
			*((unsigned int *)(offset + img->addr)) = color;
			j++;
		}
		i++;
	}
}

int	ft_blendcolors(int color1, int color2, float alpha)
{
	if (alpha < 0.0) alpha = 0.0;
	if (alpha > 1.0) alpha = 1.0;

	unsigned char r1 = (color1 >> 16) & 0xFF;
	unsigned char g1 = (color1 >> 8) & 0xFF;
	unsigned char b1 = color1 & 0xFF;

	unsigned char r2 = (color2 >> 16) & 0xFF;
	unsigned char g2 = (color2 >> 8) & 0xFF;
	unsigned char b2 = color2 & 0xFF;

	unsigned char r = (unsigned char)((r1 * alpha) + (r2 * (1 - alpha)));
	unsigned char g = (unsigned char)((g1 * alpha) + (g2 * (1 - alpha)));
	unsigned char b = (unsigned char)((b1 * alpha) + (b2 * (1 - alpha)));

	return (r << 16) | (g << 8) | b;
}
