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
	int	offset;
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 3;
	// size = 5;
	// x *= size;
	// y *= size;
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
