/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_walls_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:02:43 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/28 18:01:07 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
void	ft_define_steps(t_raycast *ray)
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
 * @brief Calculates the wall height and rendering bounds.
 * 
 * This function determines the perpendicular wall distance based on the ray
 * hit side and the distance values computed during raycasting. If the ray's
 * step position is outisde the map bounds, it sets the perpendicular wall
 * distance to 0. It then calculates the height of the wall slice that will be
 * drawn on the screen, as well as the start and end positions for rendering.
 * 
 * @param ray Pointer to the raycasting structure containing ray information.
 * @param map Pointer to the map structure containing level data.
 */
static void	ft_get_wall_height(t_raycast *ray, t_map *map)
{
	if (!(ray->step_squ.x >= 0 && ray->step_squ.x < map->height
			&& ray->step_squ.y >= 0 && ray->step_squ.y < map->width
			&& map->matrix[ray->step_squ.x][ray->step_squ.y]))
		ray->perp_wall_dist = 0;
	if (ray->hit_side == 0)
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
	if (ray->hit_side == 0)
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
	bool	stop_loop;

	w = 0;
	while (w < WIDTH)
	{
		ft_get_ray_info(cub->raycast, w);
		ft_define_steps(cub->raycast);
		stop_loop = false;
		while (!stop_loop)
			ft_dda(cub->raycast, cub->map, &stop_loop);
		ft_get_wall_height(cub->raycast, cub->map);
		ft_get_wall_hit_value(cub->raycast);
		if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x < 0)
			ft_paint_ray(cub, w, cub->raycast->north_texture);
		if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x >= 0)
			ft_paint_ray(cub, w, cub->raycast->south_texture);
		if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y >= 0)
			ft_paint_ray(cub, w, cub->raycast->east_texture);
		if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y < 0)
			ft_paint_ray(cub, w, cub->raycast->west_texture);
		cub->raycast->buffer[w] = cub->raycast->perp_wall_dist;
		//printf("buffer[%d]: %lf\n", w, cub->raycast->buffer[w]); //debug
		w++;
	}
}
