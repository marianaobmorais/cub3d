/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_action_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:53:48 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/09 19:55:55 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Paints a source image onto the main image with blending.
 *
 * This function iterates over the pixels of the source image and blends 
 * each pixel with the corresponding pixel in the main image. The blending 
 * is done based on a given alpha value (`t`), and the color is applied 
 * to the main image at the specified position. If the source pixel color 
 * is `IGNORE`, it will keep the default color from the main image.
 *
 * @param cub The main game structure containing the current image.
 * @param source The source image to be painted onto the main image.
 * @param p The position where the source image will be painted on the 
 *          main image (offset by `p.x` and `p.y`).
 * @param t The alpha value for blending the two colors (0.0 to 1.0).
 */
static void	ft_paint_on_image(t_cub *cub, t_image *source, t_ipoint p, double t)
{
	int	source_color;
	int	default_color;
	int	blend;
	int	y;
	int	x;

	x = 0;
	while (x < source->height)
	{
		y = 0;
		while (y < source->width)
		{
			default_color = ft_get_pixel_color(cub->image, \
				x + p.x, y + p.y, cub);
			source_color = ft_get_pixel_color(source, x, y, cub);
			blend = ft_blendcolors(default_color, source_color, t);
			if (source_color == IGNORE)
				ft_put_pixel(cub->image, x + p.x, y + p.y, default_color);
			else
				ft_put_pixel(cub->image, x + p.x, y + p.y, blend);
			y++;
		}
		x++;
	}
}

/**
 * @brief Renders the action (e.g., breadcrumbs) on the screen with progress.
 *
 * This function paints the breadcrumbs image onto the main image at a 
 * specified position, based on the current action's duration. The blending 
 * of the breadcrumbs image is controlled by the `duration_action` value, 
 * which is incremented by the frame time (`frame_time`). If the action 
 * duration exceeds 0.5s, the action is stopped and the duration is reset.
 *
 * @param cub The main game structure containing the HUD and action data.
 */
void	ft_render_action(t_cub *cub)
{
	//add brief
	t_ipoint	pos;

	if (cub->action)
	{
		pos.x = 200;
		pos.y = HEIGHT - cub->hud->breadcrumbs.height;
		ft_paint_on_image(cub, &cub->hud->breadcrumbs, pos, cub->duration_action);
		cub->duration_action += cub->frame_time;
		if (cub->duration_action >= 0.5)
		{
			cub->action = false;
			cub->duration_action = 0;
		}
	}
	if (cub->raycast->sprite_action)
	{
		cub->raycast->eat_time += cub->frame_time;
		if (cub->raycast->eat_time >= 4)
		{
			cub->raycast->sprite_action = false;
			cub->raycast->eat_time = 0;
		}
	}
}
