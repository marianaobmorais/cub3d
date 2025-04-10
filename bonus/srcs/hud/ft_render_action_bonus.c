/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_action_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:53:48 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/10 20:44:17 by joneves-         ###   ########.fr       */
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
 * @brief Handles the rendering of actions in the game, such as displaying
 *        HUD elements for actions and managing sprite actions.
 *
 * This function updates the state of the action and sprite actions, 
 * including rendering action icons on the HUD. It also manages the 
 * duration of the action and the sprite action (e.g., eating time).
 *
 * @param cub The game structure containing relevant data, including action 
 *            durations, sprite actions, and HUD elements.
 */
void	ft_render_action(t_cub *cub)
{
	t_ipoint	pos;

	if (cub->action)
	{
		pos.x = 200;
		pos.y = HEIGHT - cub->hud->breadcrumbs.height;
		ft_paint_on_image(cub, &cub->hud->breadcrumbs, pos, \
			cub->duration_action);
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
