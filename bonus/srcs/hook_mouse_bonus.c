/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 17:17:59 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Handles mouse-based view rotation in the game loop.
 *
 * Checks mouse position relative to the center of the screen and 
 * rotates the player's view accordingly, simulating a first-person 
 * look mechanic. Resets the mouse to the center every 0.05 seconds 
 * to maintain continuous movement without bounds issues.
 *
 * @param cub Pointer to the main game structure.
 * @return Always returns 0 (standard for hook functions).
 */
int	ft_mouse_hook(t_cub *cub)
{
	cub->raycast->mouse_time += cub->frame_time;
	if (cub->raycast->mouse_time >= 0.05)
	{
		mlx_mouse_get_pos(cub->mlx, cub->window, &cub->raycast->mouse_pos.x, \
			&cub->raycast->mouse_pos.y);
		if ((cub->raycast->mouse_pos.x >= 0
				&& cub->raycast->mouse_pos.x < WIDTH / 2))
			ft_rotate(cub, cub->raycast->move_speed);
		if ((cub->raycast->mouse_pos.x > WIDTH / 2
				&& cub->raycast->mouse_pos.x < WIDTH))
			ft_rotate(cub, -cub->raycast->move_speed);
		cub->raycast->mouse_time = 0;
	}
	mlx_mouse_move(cub->mlx, cub->window, WIDTH / 2, HEIGHT / 2);
	return (0);
}
