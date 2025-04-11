/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_ray_door_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:06:16 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/10 21:07:37 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Calculates drawing parameters for rendering a door slice.
 *
 * Prepares the vertical slice of a door texture to be drawn by computing the
 * height, texture coordinates, and initial texture position based on the
 * door's distance from the player and wall hit position.
 *
 * @param cub A pointer to the main game structure.
 * @param door A pointer to the door structure to set up.
 */
static void	ft_prepare_door_draw(t_cub *cub, t_door *door)
{
	t_draw	*draw;

	draw = &door->draw;
	draw->height = (int)(HEIGHT / door->door_dist);
	draw->draw_start = -draw->height / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->height / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
	draw->tex_x = (int)(door->wall_hit * door->current.width);
	if ((door->door_side == 0 && cub->raycast->ray_dir.x > 0)
		|| (door->door_side == 1 && cub->raycast->ray_dir.y < 0))
		draw->tex_x = door->current.width - draw->tex_x - 1;
	draw->tex_x %= door->current.width;
	draw->step = (double)door->current.height / draw->height;
	draw->texture_pos = (draw->draw_start - HEIGHT / 2 + draw->height / 2) \
		* draw->step;
}

/**
 * @brief Draws a vertical slice of a door texture on the screen.
 *
 * This function paints a single vertical line (ray) of a door texture onto the
 * main image buffer. It uses precomputed drawing parameters and skips pixels
 * with the IGNORE color (transparent).
 *
 * @param cub A pointer to the main game structure.
 * @param w The x-coordinate on the screen where the slice is drawn.
 * @param door The door structure containing texture and drawing info.
 */
void	ft_paint_ray_door(t_cub *cub, int w, t_door door)
{
	t_draw	*draw;
	int		y;
	int		tex_y;
	int		color;

	draw = &door.draw;
	ft_prepare_door_draw(cub, &door);
	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		tex_y = (int)(draw->texture_pos);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= door.current.height)
			tex_y = door.current.height - 1;
		draw->texture_pos += draw->step;
		color = ft_get_pixel_color(&door.current, draw->tex_x, tex_y, cub);
		if (color != IGNORE)
			ft_put_pixel(cub->image, w, y, color);
		y++;
	}
}
