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

/**
 * @brief Draws a small player marker on the given image.
 *
 * This function renders a 5x5 pixel square to represent the player's 
 * position on the minimap with a specified color.
 *
 * @param img Pointer to the image where the player marker will be drawn.
 * @param x X-coordinate (scaled by square size).
 * @param y Y-coordinate (scaled by square size).
 * @param color Color of the player marker.
 */
void	ft_put_player(t_image *img, int x, int y, int color)
{
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

/**
 * @brief Blends two colors based on an alpha value.
 *
 * This function computes a weighted average of two colors (color1 and color2) 
 * using an alpha value, where alpha controls the blending ratio. The result 
 * is a new color formed by blending the two input colors.
 *
 * @param color1 First color (in RGB format).
 * @param color2 Second color (in RGB format).
 * @param alpha Blending factor between 0.0 and 1.0, where 0.0 means 
 *              full color1 and 1.0 means full color2.
 * 
 * @return The resulting blended color in RGB format.
 */
int	ft_blendcolors(int color1, int color2, float alpha)
{
	unsigned char	r1;
	unsigned char	g1;
	unsigned char	b1;
	unsigned char	r2;
	unsigned char	g2;
	unsigned char	b2;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (alpha < 0.0)
		alpha = 0.0;
	if (alpha > 1.0)
		alpha = 1.0;
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	r = (unsigned char)((r1 * alpha) + (r2 * (1 - alpha)));
	g = (unsigned char)((g1 * alpha) + (g2 * (1 - alpha)));
	b = (unsigned char)((b1 * alpha) + (b2 * (1 - alpha)));
	return ((r << 16) | (g << 8) | b);
}
