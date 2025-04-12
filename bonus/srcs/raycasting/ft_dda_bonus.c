/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:30:11 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 16:16:26 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Records information about a door tile hit during raycasting.
 *
 * When a door tile ('D') is encountered during the DDA traversal, this function
 * logs the door's grid position, determines which side of the wall the ray hit,
 * and calculates the perpendicular distance to the door. It updates the
 * relevant `door` entry in the map using the tile coordinates and side of
 * impact.
 *
 * @param ray Pointer to the raycasting structure containing the current ray
 *        state.
 * @param cub Pointer to the main game structure containing map and door data.
 */
static void	ft_get_door_info(t_raycast *ray, t_map *map, t_cub *cub)
{
	int	index;

	ray->door_increment++;
	if (ray->door_increment == -1)
		return ;
	ray->doors_found[ray->door_increment].x = ray->step_tile.x;
	ray->doors_found[ray->door_increment].y = ray->step_tile.y;
	index = ft_find_door_index(cub, ray->step_tile.x, ray->step_tile.y);
	ray->hit_door = true;
	map->door[index].door_tile = ray->step_tile;
	map->door[index].door_side = ray->hit_side;
	if (ray->hit_side == 0)
		map->door[index].door_dist = ray->dist_to_x - ray->delta_dist_x;
	else
		map->door[index].door_dist = ray->dist_to_y - ray->delta_dist_y;
}

/**
 * @brief Performs the DDA (Digital Differential Analysis) algorithm for
 *        raycasting.
 * 
 * This function increments the ray step-by-step through the 2D grid until it 
 * encounters a wall. It determines whether the next step should be in the 
 * x-direction or y-direction based on the smallest distance increment. The 
 * function updates the current grid position of the ray and records which 
 * side of the wall or door was hit, or it goes outbounds. If hit side is 0, it
 * means it is either North or South walls, if it is 1, it is either East or
 * West walls.
 * 
 * @param ray Pointer to the raycasting structure holding current step and
 *        distance data.
 * @param map Pointer to the map structure containing the tile matrix.
 * @param stop_loop Pointer to a boolean flag that will be set to true if a wall
 *        or map boundary is hit.
 * @param cub Pointer to the main game structure, used to access door 
 *        information if needed.
 */
void	ft_dda(t_raycast *ray, t_map *map, bool *stop_loop, t_cub *cub)
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
		if (map->matrix[ray->step_tile.x][ray->step_tile.y] == 'D')
			ft_get_door_info(ray, map, cub);
		if (map->matrix[ray->step_tile.x][ray->step_tile.y] == '1')
			*stop_loop = true;
	}
	else
		*stop_loop = true;
}
