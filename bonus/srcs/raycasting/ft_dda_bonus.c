/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:30:11 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/07 15:50:19 by mariaoli         ###   ########.fr       */
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
void	ft_dda(t_raycast *ray, t_map *map, bool *stop_loop, t_cub *cub, bool fov)
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
		if (map->matrix[ray->step_tile.x][ray->step_tile.y] == 'D' && fov)
		{
			cub->raycast->door_increment++;
			cub->raycast->doors_found[cub->raycast->door_increment].x = ray->step_tile.x;
			cub->raycast->doors_found[cub->raycast->door_increment].y = ray->step_tile.y;
			//printf("ray steps--> x %d y %d\n", ray->step_tile.x, ray->step_tile.y);
			int index = ft_find_door_index(cub, ray->step_tile.x, ray->step_tile.y);
			//printf("\n \n \n index -> %d \n \n \n", index);
			ray->hit_door = true;
			cub->map->door[index].door_tile = ray->step_tile;
			cub->map->door[index].door_side = ray->hit_side;
			if (ray->hit_side == 0)
				(cub->map->door)[index].door_dist = ray->dist_to_x - ray->delta_dist_x;
			else
				(cub->map->door)[index].door_dist = ray->dist_to_y - ray->delta_dist_y;
		}
		if (map->matrix[ray->step_tile.x][ray->step_tile.y] == '1')
			*stop_loop = true;
	}
	else
		*stop_loop = true;
}
