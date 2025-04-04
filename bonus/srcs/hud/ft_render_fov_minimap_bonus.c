/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_fov_minimap_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:13:41 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/02 21:10:11 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

void	raycast_minimap(t_cub *cub, t_raycast ray, double angle)
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
		ft_dda(&ray, cub->map, &hit_wall);
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
