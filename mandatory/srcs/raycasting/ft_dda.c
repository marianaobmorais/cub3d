#include "../../includes/cub3d.h"

/**
 * @brief Performs the DDA (Digital Differential Analysis) algorithm for
 *        raycasting.
 * 
 * This function increments the ray step-by-step through the 2D grid until it 
 * encounters a wall. It determines whether the next step should be in the 
 * x-direction or y-direction based on the smallest distance increment. The 
 * function updates the current grid position of the ray and records which 
 * side of the wall was hit.
 * 
 * @param ray Pointer to the raycasting structure containing ray information.
 * @param map Pointer to the map structure that holds the world matrix.
 * @param hit_wall Pointer to a boolean that is set to true if a wall is hit.
 */
void	ft_dda(t_raycast *ray, t_map *map, bool *hit_wall)
{
	if (ray->dist_to_x < ray->dist_to_y)
	{
		ray->dist_to_x += ray->delta_dist_x;
		ray->step_squ.x += ray->step.x;
		if (ray->ray_dir.x < 0)
			ray->hit_side = NORTH;
		else
			ray->hit_side = SOUTH;
	}
	else
	{
		ray->dist_to_y += ray->delta_dist_y;
		ray->step_squ.y += ray->step.y;
		if (ray->ray_dir.y < 0)
			ray->hit_side = WEST;
		else
			ray->hit_side = EAST;
	}
	if (map->matrix[ray->step_squ.x][ray->step_squ.y] 
		&& map->matrix[ray->step_squ.x][ray->step_squ.y] == '1')
		*hit_wall = true;
}
