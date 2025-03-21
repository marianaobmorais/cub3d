#include "../../includes/cub3d.h"

// /**
//  * @brief Retrieves the color of a specific pixel from an image.
//  *
//  * This function calculates the pixel's memory address based on the 
//  * given coordinates (x, y) and returns the color value at that 
//  * position in the image.
//  *
//  * @param x X-coordinate of the pixel.
//  * @param y Y-coordinate of the pixel.
//  * @param source Pointer to the image from which the pixel color is fetched.
//  * 
//  * @return The color of the pixel at the given coordinates.
//  */
// int	ft_get_pixel_color_other(int x, int y, t_image *source)
// {
// 	char	*addr;
// 	char	*dst;
// 	int		offset;

// 	addr = source->addr ;
// 	offset = (y * source->line_len) + (x * (source->bpp / 8));
// 	dst = offset + addr;
// 	return (*(unsigned int *)dst);
// }

/**
 * @brief Paints the source image onto the HUD at a specific position.
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
void	ft_paint_source_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y)
{
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
			source_color = ft_get_pixel_color(source, x, y);
			if (source_color == IGNORE)
			{
				default_color = ft_get_pixel_color(cub->image, x + pos_x, y + pos_y);
				ft_put_pixel(cub->image, x + pos_x, y + pos_y, default_color);
			}
			else
				ft_put_pixel(cub->image, x + pos_x, y + pos_y, source_color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders the HUD (Heads-Up Display) components on the screen.
 *
 * This function paints various HUD elements, such as the watch, viewmodel, 
 * breadcrumbs, and the minimap, onto the HUD layer. It calls specific 
 * functions to draw each component at predefined positions on the screen.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_put_hud(t_cub *cub)
{
	// if (cub->hud->img->img_ptr)
	// 	mlx_destroy_image(cub->mlx, cub->hud->img->img_ptr);
	// cub->hud->img->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (!cub->hud->img->img_ptr)
	// 	ft_handle_error("malloc: hud->img_ptr", cub);
	// cub->hud->img->bpp = 0;
	// cub->hud->img->line_len = 0;
	// cub->hud->img->endian = 0;
	// cub->hud->img->addr = mlx_get_data_addr(cub->hud->img->img_ptr, 
	// 	&cub->hud->img->bpp, &cub->hud->img->line_len, &cub->hud->img->endian);
	// if (!cub->hud->img->addr)
	// 	ft_handle_error("malloc: img->addr", cub);
	//ft_paint_source_on_hud(cub, cub->image, 0, 0); //paint main image
	ft_paint_source_on_hud(cub, cub->hud->watch, 0, 0);
	ft_paint_source_on_hud(cub, cub->hud->viewmodel, 390, 420);
	ft_paint_source_on_hud(cub, cub->hud->breads, 820, 0);
	ft_paint_minimap_on_hud(cub); //minimap
	//ft_door(cub, cub->hud->door, 420, 300);
}
