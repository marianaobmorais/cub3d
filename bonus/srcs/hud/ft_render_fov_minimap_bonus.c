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

static void	ft_get_wall_minimap(t_raycast *ray, bool hit_wall)
{
	double	max_dist;

	max_dist = 8;
	if (ray->hit_side == NORTH || ray->hit_side == SOUTH)
		ray->perp_wall_dist = ray->dist_to_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->dist_to_y - ray->delta_dist_y;
	if (!hit_wall || ray->perp_wall_dist > max_dist)
		ray->perp_wall_dist = max_dist;
}

void	draw_line_minimap(t_cub *cub, int x1, int y1, int x2, int y2, int color)
{
	t_ipoint	dist; // utilizar dpoint
	t_ipoint	dir;
	int			err;
	int			blend;
	int			default_color;

	dist.y = abs(y2 - y1);
	dist.x = abs(x2 - x1);
	err = dist.x - dist.y;
	if (x1 < x2)
		dir.x = 1;
	else
		dir.x = -1;
	if (y1 < y2)
		dir.y = 1;
	else
		dir.y = -1;
	while (x1 != x2 || y1 != y2)
	{
		default_color = ft_get_pixel_color(cub->image, x1, y1, cub);
		//printf("cor-> %d\n", default_color);// debug
		blend = ft_blendcolors(default_color, color, 0.9);
		ft_put_pixel(cub->image, x1, y1, blend);
		int e2 = err * 2;
		if (e2 > -dist.y)
		{
			err -= dist.y;
			x1 += dir.x;
		}
		if (e2 < dist.x)
		{
			err += dist.x;
			y1 += dir.y;
		}
	}
}

void	raycast_minimap(t_cub *cub, t_raycast ray,double angle)
{
	bool		hit_wall;
	int			steps;
	t_dpoint	hit;

	hit_wall = false;
	ray.player_pos.x = cub->raycast->player_pos.x;
	ray.player_pos.y = cub->raycast->player_pos.y;
	ray.player_squ.x = (int) ray.player_pos.x;
	ray.player_squ.y = (int) ray.player_pos.y;
	ray.ray_dir.x = sin(angle);
	ray.ray_dir.y = cos(angle);
	ft_define_steps(&ray); //original
	ft_get_ray_info_minimap(&ray); //copy
	steps = 0;
	while (!hit_wall && steps < 10)
	{
		ft_dda(&ray, cub->map, &hit_wall);
		steps++;
	}
	ft_get_wall_minimap(&ray, hit_wall);
	hit.x = ray.player_pos.x + ray.perp_wall_dist * ray.ray_dir.x;
	hit.y = ray.player_pos.y + ray.perp_wall_dist * ray.ray_dir.y;
	ray.player_squ.x = (ray.player_pos.x - cub->hud->start_x) * TILE + OFFSET_X;
	ray.player_squ.y = (ray.player_pos.y - cub->hud->start_y) * TILE + OFFSET_Y;
	hit.x = (hit.x - cub->hud->start_x) * TILE + OFFSET_X;
	hit.y = (hit.y - cub->hud->start_y) * TILE + OFFSET_Y;
	draw_line_minimap(cub, ray.player_squ.y, ray.player_squ.x, (int) hit.y, (int) hit.x, GREEN2);
	ft_put_player(cub->image, ray.player_squ.y, ray.player_squ.x, RED);
}

void	ft_render_fov_minimap(t_cub *cub)
{
	t_raycast	*ray;
	int			i;
	int			num_rays;
	double		player_angle;
	double		angle_start;
	double		angle;

	ray = (t_raycast *) malloc(sizeof(t_raycast));
	player_angle = atan2(cub->raycast->player_dir.x, cub->raycast->player_dir.y);
	angle_start = player_angle - (FOV / 2);
	num_rays = 120;
	i = 0;
	while (i < num_rays)
	{
		angle = angle_start + i * (FOV / (num_rays));
		raycast_minimap(cub, *ray, angle);
		i++;
	}
	free(ray);
}
