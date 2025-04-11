/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_fov_minimap_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:13:41 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/10 21:03:36 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Calculates the raycasting parameters needed for rendering the minimap.
 *
 * This function computes the ray's distance and delta distance in both the x 
 * and y directions. It calculates the initial distances to the next vertical 
 * and horizontal grid lines based on the player's position and the ray's 
 * direction. These values are necessary for raycasting algorithms to determine 
 * the intersection points with the walls.
 *
 * @param ray The raycast structure containing the player's position and ray 
 *            direction, which will be updated with the calculated distances.
 */
static void	ft_get_ray_info_minimap(t_raycast *ray)
{
	if (ray->ray_dir.x == 0)
		ray->delta_dist_x = INT_MAX;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist_y = INT_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir.y);
	if (ray->ray_dir.x < 0)
		ray->dist_to_x = (ray->player_pos.x - (double)ray->player_tile.x)
			* ray->delta_dist_x;
	else
		ray->dist_to_x = ((double)ray->player_tile.x + 1.0 - ray->player_pos.x)
			* ray->delta_dist_x;
	if (ray->ray_dir.y < 0)
		ray->dist_to_y = (ray->player_pos.y - (double)ray->player_tile.y)
			* ray->delta_dist_y;
	else
		ray->dist_to_y = ((double)ray->player_tile.y + 1.0 - ray->player_pos.y)
			* ray->delta_dist_y;
}

/**
 * @brief Calculates the perpendicular dist to the wall for minimap rendering.
 *
 * This function computes the perpendicular distance from the player's position 
 * to the nearest wall, based on the ray's direction and the side it hit. The 
 * function ensures the calculated distance does not exceed a maximum value, 
 * which is useful for rendering walls within a reasonable range on the minimap.
 *
 * @param ray The raycast structure containing the ray's distance and side, 
 *            which will be updated with the perpendicular wall distance.
 * @param hit_wall A flag indicating whether the ray hit a wall. If false, 
 *                 the wall distance is set to a maximum value.
 */
static void	ft_get_wall_minimap(t_raycast *ray, bool hit_wall)
{
	double	max_dist;

	max_dist = 30;
	if ((ray->hit_side == 0 && ray->ray_dir.x < 0)
		|| (ray->hit_side == 0 && ray->ray_dir.x >= 0))
		ray->perp_wall_dist = ray->dist_to_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->dist_to_y - ray->delta_dist_y;
	if (!hit_wall || ray->perp_wall_dist > max_dist)
		ray->perp_wall_dist = max_dist;
}

/**
 * @brief Initializes the raycast structure based on the player's position 
 *        and the given angle.
 *
 * This function sets up the raycast structure with the player's position and 
 * tile coordinates, and calculates the direction of the ray based on the 
 * specified angle. It also defines the ray's step values and computes the 
 * ray's information for minimap rendering.
 *
 * @param cub The main game structure, which contains the player's position.
 * @param ray The raycast structure to be initialized.
 * @param angle The angle at which the ray is cast, typically based on 
 *              player orientation.
 */
static void	setting_raycast(t_cub *cub, t_raycast *ray, double angle)
{
	ray->player_pos.x = cub->raycast->player_pos.x;
	ray->player_pos.y = cub->raycast->player_pos.y;
	ray->player_tile.x = (int) ray->player_pos.x;
	ray->player_tile.y = (int) ray->player_pos.y;
	ray->ray_dir.x = sin(angle);
	ray->ray_dir.y = cos(angle);
	ft_define_steps(ray);
	ft_get_ray_info_minimap(ray);
}

/**
 * @brief Performs a raycast for minimap rendering, tracing a ray at the given 
 *        angle and updating the minimap with the player's position and ray hit.
 *
 * This function casts a ray from the player's position in the specified 
 * direction (angle), performing the DDA (Digital Differential Analyzer) 
 * algorithm to trace the ray until it hits a wall or reaches a maximum number 
 * of steps. It then calculates the hit position and draws the ray and player 
 * position on the minimap.
 *
 * @param cub The main game structure, which contains the player's position, 
 *            map data, and HUD settings.
 * @param ray The raycast structure to be used for tracing the ray.
 * @param angle The angle at which the ray is cast, typically based on the 
 *              player's orientation.
 */
static void	raycast_minimap(t_cub *cub, t_raycast ray, double angle)
{
	t_dpoint	hit;
	t_ipoint	ihit;
	bool		hit_wall;
	int			steps;

	hit_wall = false;
	setting_raycast(cub, &ray, angle);
	steps = 0;
	while (!hit_wall && steps < 10)
	{
		ft_dda(&ray, cub->map, &hit_wall, cub, false);
		steps++;
	}
	ft_get_wall_minimap(&ray, hit_wall);
	hit.x = ray.player_pos.x + ray.perp_wall_dist * ray.ray_dir.x;
	hit.y = ray.player_pos.y + ray.perp_wall_dist * ray.ray_dir.y;
	ray.player_tile.x = (ray.player_pos.x - cub->hud->start_x) * TILE + \
		(9 * TILE);
	ray.player_tile.y = (ray.player_pos.y - cub->hud->start_y) * TILE + \
		(4 * TILE);
	ihit.x = (int)((hit.x - cub->hud->start_x) * TILE + (9 * TILE));
	ihit.y = (int)((hit.y - cub->hud->start_y) * TILE + (4 * TILE));
	ft_draw_line(cub, ray.player_tile, ihit, GREEN2);
	ft_put_player(cub->image, ray.player_tile.y, ray.player_tile.x, RED);
}

/**
 * @brief Renders the player's field of view (FOV) on the minimap.
 *
 * This function casts rays in the player's field of view (FOV) and draws them 
 * on the minimap to represent the visible area. It calculates the start angle 
 * based on the player's current direction and casts rays at intervals across 
 * the FOV. The rays are used to update the minimap with the player's vision.
 *
 * @param cub The main game structure, containing the player's position, 
 *            direction, and the map.
 */
void	ft_render_fov_minimap(t_cub *cub)
{
	t_raycast	*ray;
	int			i;
	double		player_angle;
	double		angle_start;
	double		angle;

	ray = (t_raycast *) malloc(sizeof(t_raycast));
	if (!ray)
		ft_handle_error("malloc: hud ray", cub);
	player_angle = atan2(cub->raycast->player_dir.x, \
		cub->raycast->player_dir.y);
	angle_start = player_angle - (FOV / 2);
	i = 0;
	while (i < 120)
	{
		angle = angle_start + i * (FOV / 120);
		raycast_minimap(cub, *ray, angle);
		i++;
	}
	free(ray);
}
