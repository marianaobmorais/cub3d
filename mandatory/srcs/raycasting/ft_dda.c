/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:20:33 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/30 16:59:04 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Performs the DDA (Digital Differential Analysis) algorithm for
 *        raycasting.
 * 
 * This function increments the ray step-by-step through the 2D grid until it 
 * encounters a wall. It determines whether the next step should be in the 
 * x-direction or y-direction based on the smallest distance increment. The 
 * function updates the current grid position of the ray and records which 
 * side of the wall was hit, or it goes outbounds. If hit side is 0, it means it
 * is either North or South walls, if it is 1, it is either East or West walls.
 * 
 * @param ray Pointer to the raycasting structure containing ray information.
 * @param map Pointer to the map structure that holds the world matrix.
 * @param stop_loop Pointer to a boolean that is set to true if a wall is hit.
 */
void	ft_dda(t_raycast *ray, t_map *map, bool *stop_loop)
{
	if (ray->dist_to_x < ray->dist_to_y)
	{
		ray->dist_to_x += ray->delta_dist_x;
		ray->step_tile.x += ray->step.x;
		ray->hit_side = 0;
	}
	else
	{
		ray->dist_to_y += ray->delta_dist_y;
		ray->step_tile.y += ray->step.y;
		ray->hit_side = 1;
	}
	if (ray->step_tile.x >= 0 && ray->step_tile.x < map->height
		&& ray->step_tile.y >= 0 && ray->step_tile.y < map->width
		&& map->matrix[ray->step_tile.x][ray->step_tile.y])
	{
		if (map->matrix[ray->step_tile.x][ray->step_tile.y] == '1')
			*stop_loop = true;
	}
	else
		*stop_loop = true;
}
