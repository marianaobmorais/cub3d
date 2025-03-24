/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_ray_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:09:35 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/22 19:30:42 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Paints a vertical strip of a wall texture onto the screen.
 * 
 * This function takes the calculated texture coordinates and maps them to a
 * vertical stripe on the screen at the given window width. It adjusts the
 * texture coordinates for wall orientation and ensures they remain within
 * bounds. Then, it iterates over the vertical segment of the screen, sampling
 * texture colors and placing pixels accordingly.
 * 
 * @param cub The main structure containing game and rendering data.
 * @param window_w The x-coordinate of the vertical stripe in the window.
 * @param texture The texture image to apply.
 */
void	ft_paint_ray(t_cub *cub, int window_w, t_image texture)
{
	double			step;
	int				texture_w;
	int				texture_h;
	int				window_h;
	unsigned int	color;

	texture_w = (int)(cub->raycast->wall_hit_value * (double)texture.width);
	if (cub->raycast->hit_side == SOUTH)
		texture_w = texture.width - texture_w - 1;
	if (cub->raycast->hit_side == EAST)
		texture_w = texture.width - texture_w - 1;
	texture_w = texture_w % texture.width;
	step = 1.0 * ((double) texture.height / cub->raycast->wall_height);
	cub->raycast->texture_pos = (cub->raycast->wall_start - HEIGHT / 2
			+ cub->raycast->wall_height / 2) * step;
	window_h = cub->raycast->wall_start;
	while (window_h <= cub->raycast->wall_end)
	{
		texture_h = (int)cub->raycast->texture_pos % texture.height;
		cub->raycast->texture_pos += step;
		color = ft_get_pixel_color(&texture, texture_w, texture_h, cub);
		ft_put_pixel(cub->image, window_w, window_h, color);
		window_h++;
	}
}
