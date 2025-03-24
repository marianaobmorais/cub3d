/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:02:43 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/22 19:17:58 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Computes ray direction and distance calculations.
 *
 * Determines the direction of a ray cast from the player's position and
 * calculates how far the ray has to travel in world space to cross one grid
 * line in the X or Y direction (delta_dist).
 *
 * @param ray A pointer to the raycasting structure.
 * @param w The current screen column.
 */
static void	ft_get_ray_info(t_raycast *ray, int w)
{
	ray->factor = 2 * ((double)w / WIDTH) - 1;
	ray->ray_dir.x = ray->player_dir.x + (ray->camera_plane.x * ray->factor);
	ray->ray_dir.y = ray->player_dir.y + (ray->camera_plane.y * ray->factor);
	if (ray->ray_dir.x == 0)
		ray->delta_dist_x = INT_MAX;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist_y = INT_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir.y);
	if (ray->ray_dir.x < 0)
		ray->dist_to_x = (ray->player_pos.x - (double)ray->player_squ.x)
			* ray->delta_dist_x;
	else
		ray->dist_to_x = ((double)ray->player_squ.x + 1.0 - ray->player_pos.x)
			* ray->delta_dist_x;
	if (ray->ray_dir.y < 0)
		ray->dist_to_y = (ray->player_pos.y - (double)ray->player_squ.y)
			* ray->delta_dist_y;
	else
		ray->dist_to_y = ((double)ray->player_squ.y + 1.0 - ray->player_pos.y)
			* ray->delta_dist_y;
}

/**
 * @brief Defines the step direction for the ray.
 *
 * Determines in which direction (left/right, up/down) the ray will step in
 * world space.
 *
 * @param ray A pointer to the raycasting structure.
 */
static void	ft_define_steps(t_raycast *ray)
{
	ray->step_squ.x = ray->player_squ.x;
	ray->step_squ.y = ray->player_squ.y;
	if (ray->ray_dir.x < 0)
		ray->step.x = -1;
	else
		ray->step.x = 1;
	if (ray->ray_dir.y < 0)
		ray->step.y = -1;
	else
		ray->step.y = 1;
}

/**
 * @brief Calculates the height of walls based on ray distance.
 *
 * Determines the projected height of walls to be drawn on the screen
 * based on the distance from the player. perp_wall_dist gets get point in the
 * camera plane closest to the hitpoint of the ray. wall_height is the inverse
 * of perp_wall_dist, and then multiplied by h, the height in pixels of the 
 * screen, to bring it to pixel coordinates.
 *
 * @param ray A pointer to the raycasting structure.
 */
static void	ft_get_wall_height(t_raycast *ray)
{
	if (ray->hit_side == NORTH || ray->hit_side == SOUTH)
		ray->perp_wall_dist = ray->dist_to_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->dist_to_y - ray->delta_dist_y;
	ray->wall_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->wall_start = -(ray->wall_height / 2) + (HEIGHT / 2);
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = (ray->wall_height / 2) + (HEIGHT / 2);
	if (ray->wall_end >= HEIGHT)
		ray->wall_end = HEIGHT - 1;
}

/**
 * @brief Computes the exact position where a ray hits a wall.
 *
 * Determines the texture coordinate for proper texture mapping.
 *
 * @param ray A pointer to the raycasting structure.
 */
static void	ft_get_wall_hit_value(t_raycast *ray)
{
	if (ray->hit_side == NORTH || ray->hit_side == SOUTH)
		ray->wall_hit_value = ray->player_pos.y + ray->perp_wall_dist
			* ray->ray_dir.y;
	else
		ray->wall_hit_value = ray->player_pos.x + ray->perp_wall_dist
			* ray->ray_dir.x;
	ray->wall_hit_value -= floor(ray->wall_hit_value);
}

/**
 * @brief Renders walls using raycasting.
 *
 * Iterates through screen columns, casts rays, determines wall hit points,
 * and renders the corresponding textures.
 *
 * @param cub A pointer to the game structure.
 */
void	ft_render_walls(t_cub *cub)
{
	int		w;
	bool	hit_wall;

	w = 0;
	while (w < WIDTH)
	{
		ft_get_ray_info(cub->raycast, w);
		ft_define_steps(cub->raycast);
		hit_wall = false;
		while (!hit_wall)
			ft_dda(cub->raycast, cub->map, &hit_wall);
		ft_get_wall_height(cub->raycast);
		ft_get_wall_hit_value(cub->raycast);
		if (cub->raycast->hit_side == NORTH)
			ft_paint_ray(cub, w, cub->raycast->north_texture);
		if (cub->raycast->hit_side == SOUTH)
			ft_paint_ray(cub, w, cub->raycast->south_texture);
		if (cub->raycast->hit_side == EAST)
			ft_paint_ray(cub, w, cub->raycast->east_texture);
		if (cub->raycast->hit_side == WEST)
			ft_paint_ray(cub, w, cub->raycast->west_texture);
		w++;
	}
}
