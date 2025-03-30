/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:30:11 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/27 19:47:46 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
		ray->step_squ.x += ray->step.x;
		ray->hit_side = 0;
	}
	else
	{
		ray->dist_to_y += ray->delta_dist_y;
		ray->step_squ.y += ray->step.y;
		ray->hit_side = 1;

	}
	if (ray->step_squ.x >= 0 && ray->step_squ.x < map->height
		&& ray->step_squ.y >= 0 && ray->step_squ.y < map->width
		&& map->matrix[ray->step_squ.x][ray->step_squ.y])
	{
		if (map->matrix[ray->step_squ.x][ray->step_squ.y] == '1')
			*stop_loop = true;
	}
	else
		*stop_loop = true;
}
