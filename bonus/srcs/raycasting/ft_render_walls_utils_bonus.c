/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_walls_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:53:47 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/11 17:56:37 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Selects and paints the correct wall texture based on ray hit direction
 *
 * Determines which wall face (north, south, east, or west) was hit by the
 * current ray, and paints the corresponding vertical stripe of the wall using
 * the appropriate texture. This function ensures correct texturing based on the
 * direction the ray came from.
 *
 * @param cub Pointer to the main game structure containing raycasting and
 *        texture data.
 * @param w The x-coordinate on the screen where the wall stripe is to be drawn.
 */
void	ft_paint_external_wall(t_cub *cub, int w)
{
	if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x < 0)
		ft_paint_ray(cub, w, cub->raycast->north_texture);
	if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x >= 0)
		ft_paint_ray(cub, w, cub->raycast->south_texture);
	if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y >= 0)
		ft_paint_ray(cub, w, cub->raycast->east_texture);
	if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y < 0)
		ft_paint_ray(cub, w, cub->raycast->west_texture);
}
