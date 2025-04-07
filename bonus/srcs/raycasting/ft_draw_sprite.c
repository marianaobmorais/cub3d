/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:47:55 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/07 15:48:16 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Draws a vertical slice of the given sprite at screen column `w`.
 * 
 * This function maps each screen pixel between the sprite's vertical start and
 * end to its corresponding pixel in the sprite texture and draws it on the
 * image buffer. Transparent pixels (matching `IGNORE`) are skipped by using the
 * background color.
 *
 * @param cub Pointer to the main game structure.
 * @param sprite The sprite to be drawn.
 * @param w Screen column where the sprite slice should be drawn.
 */
void	ft_draw_sprite(t_cub *cub, t_sprite sprite, int w)
{
	int		h;
	int		texture_w;
	int		texture_h;
	int		color;

	texture_w = (int)((w - sprite.start_w) * (double)sprite.img.width \
		/ sprite.relative_width);
	h = (sprite).start_h;
	while (h < sprite.end_h)
	{
		texture_h = (int)((h - sprite.start_h) * (double)sprite.img.height \
			/ sprite.relative_height);
		if (h >= 0 && h < HEIGHT)
		{
			color = ft_get_pixel_color(&sprite.img, texture_w, texture_h, cub);
			if (color == IGNORE)
				color = ft_get_pixel_color(cub->image, w, h, cub);
			ft_put_pixel(cub->image, w, h, color);
		}
		h++;
	}
}
