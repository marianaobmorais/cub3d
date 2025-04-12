/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_img_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:57 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 18:03:57 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Handles per-frame rendering and updates for the game.
 *
 * Performs all rendering tasks for the current frame, including background, 
 * walls, doors, sprites, HUD elements, and the minimap. It also updates 
 * player movement and rotation speeds based on frame timing, and manages 
 * mouse input if active. Finally, it displays the rendered image to the 
 * game window using MLX.
 *
 * @param cub Pointer to the main game context containing all game data.
 * @return Always returns 0.
 */
int	ft_handle_img(t_cub *cub)
{
	double	normalize;

	normalize = cub->frame_time;
	ft_render_bg(cub->image, cub->map->ceiling_hex, cub->map->floor_hex);
	ft_update_doors(cub);
	ft_render_walls(cub);
	ft_render_sprites(cub);
	ft_render_source_on_hud(cub, &cub->hud->watch, 0, 0);
	ft_render_minimap_on_hud(cub);
	ft_render_viewmodel(cub);
	if (normalize > 0.02)
		normalize = 0.016;
	cub->raycast->move_speed = normalize * MOVE_SPEED;
	cub->raycast->rotate_speed = normalize * ROTATE_SPEED;
	if (!cub->raycast->mouse_status)
		ft_mouse_hook(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->image->img_ptr, 0, 0);
	return (0);
}
