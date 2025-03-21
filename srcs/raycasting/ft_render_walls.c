#include "../../includes/cub3d.h"

//factor is the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
//done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1
//the direction of the ray can be calculated as was explained earlier: as the sum of the direction vector, and a part of the plane vector.
//This has to be done both for the x and y coordinate of the vector (since adding two vectors is adding their x-coordinates, and adding their y-coordinates).
//delta_dist stores how far the ray has to travel in world space to cross one grid line in the X or Y direction.
//dist_to_x and dist_to_t store the distance from the player's position to the next grid line in both X and Y directions.
void	ft_get_ray_info(t_raycast *ray, int w)
{
	ray->factor = 2 * ((double)w / WIDTH) - 1; // or x / (double)WIDTH?
	ray->ray_dir.x = ray->player_dir.x + (ray->camera_plane.x * ray->factor);
	ray->ray_dir.y = ray->player_dir.y + (ray->camera_plane.y * ray->factor);
	if (ray->ray_dir.x == 0)
		ray->delta_dist_x = INT_MAX; //need to study this more
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist_y = INT_MAX; //need to study this more
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir.y);

	if (ray->ray_dir.x < 0)
		ray->dist_to_x = (ray->player_pos.x - (double)ray->player_squ.x) * ray->delta_dist_x;
	else
		ray->dist_to_x = ((double)ray->player_squ.x + 1.0 - ray->player_pos.x) * ray->delta_dist_x;
	if (ray->ray_dir.y < 0)
		ray->dist_to_y = (ray->player_pos.y - (double)ray->player_squ.y) * ray->delta_dist_y;
	else
		ray->dist_to_y = ((double)ray->player_squ.y + 1.0 - ray->player_pos.y) * ray->delta_dist_y;
}

//stepX and stepY determine which direction the ray moves in each axis.
//If rayDirX > 0, the ray moves right (stepX = +1), otherwise, it moves left (stepX = -1).
//If rayDirY > 0, the ray moves down (stepY = +1), otherwise, it moves up (stepY = -1).
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

void	ft_get_wall_height(t_raycast *ray)
{
	//get point in camera plane closest to the hitpoint of the ray
	if (ray->hit_side == NORTH || ray->hit_side == SOUTH) //hit_side==0
		ray->perp_wall_dist = ray->dist_to_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->dist_to_y - ray->delta_dist_y;

	//calculate the height of the line that has to be drawn on screen: this 
	//is the inverse of perpWallDist, and then multiplied by h, the height in 
	//pixels of the screen, to bring it to pixel coordinates. You can of course
	//also multiply it with another value, for example 2*h, if you want to walls
	//to be higher or lower. The value of h will make the walls look like cubes with 
	ray->wall_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->wall_start = -(ray->wall_height / 2) + (HEIGHT / 2);
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = (ray->wall_height / 2) + (HEIGHT / 2);
	if (ray->wall_end >= HEIGHT)
		ray->wall_end = HEIGHT - 1;
}

void	ft_get_wall_hit_value(t_raycast *ray)
{
	if (ray->hit_side == NORTH || ray->hit_side == SOUTH) //hit_side == 0 //hit a x axis (x value)
		ray->wall_hit_value = ray->player_pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else //hit a y axis (y value)
		ray->wall_hit_value = ray->player_pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	//wall_hit_value (aka wallX) represents the exact value where the wall was hit, not just the integer coordinates of the wall.
	//This is required to know which x-coordinate of the texture we have to use.
	//This is calculated by first calculating the exact x or y coordinate in the world,
	//and then substracting the integer value of the wall off it.
	ray->wall_hit_value -= floor(ray->wall_hit_value);
}

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
		cub->hud->ray_hits[w].x = cub->raycast->step_squ.x; //minimap
		cub->hud->ray_hits[w].y = cub->raycast->step_squ.y; //minimap
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
