#include "../../includes/cub3d.h"

/**
 * @brief Renders the source image onto the HUD at a specific position.
 *
 * This function copies pixels from the source image onto the HUD image 
 * at the specified position. Pixels with the `IGNORE` color are skipped, 
 * and the existing pixel color at that position is retained.
 *
 * @param cub Pointer to the main game structure.
 * @param source Pointer to the source image.
 * @param pos_x X-coordinate where the source image will be drawn on the HUD.
 * @param pos_y Y-coordinate where the source image will be drawn on the HUD.
 */
void	ft_render_source_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y)
{
	//update brief
	int	source_color;
	int	default_color;
	int	y;
	int	x;

	y = 0;
	while (y < source->height)
	{
		x = 0;
		while (x < source->width)
		{
			source_color = ft_get_pixel_color(source, x, y, cub);
			if (source_color == IGNORE)
			{
				default_color = ft_get_pixel_color(cub->image, x + pos_x, y + pos_y, cub);
				ft_put_pixel(cub->image, x + pos_x, y + pos_y, default_color);
			}
			else
				ft_put_pixel(cub->image, x + pos_x, y + pos_y, source_color);
			x++;
		}
		y++;
	}
}

