/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_img_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:57 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 18:06:12 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Updates sprite actions over time (e.g. eating animation).
 *
 * Iterates through all sprites in the map and, if a sprite is performing 
 * an action, increments its action timer (`eat_time`) using the frame time. 
 * Once the action duration reaches or exceeds 4 seconds, the action is 
 * stopped and the timer is reset.
 *
 * @param cub Pointer to the main game context containing map and frame data.
 */
void	ft_sprite_action(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map->sprite_count)
	{
		if (cub->map->sprite[i].sprite_action)
			cub->map->sprite[i].eat_time += cub->frame_time;
		if (cub->map->sprite[i].eat_time >= 4)
		{
			cub->map->sprite[i].sprite_action = false;
			cub->map->sprite[i].eat_time = 0;
		}
		i++;
	}
}
