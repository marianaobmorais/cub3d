#include "../../includes/cub3d.h"

void	ft_get_ray_info(t_raycast *ray, int x)
{
	//camera_curr_x is the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
	//done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1
	ray.camera_curr_x = 2 * (double)(x / WIDTH) - 1; //or (x / (double)WIDTH)?
	//the direction of the ray can be calculated as was explained earlier: as the sum of the direction vector, and a part of the plane vector.
	//This has to be done both for the x and y coordinate of the vector (since adding two vectors is adding their x-coordinates, and adding their y-coordinates).
	ray->ray_dir.x = ray->player_dir.x + ray->camera_plane.x * ray->camera_curr_x;
	ray->ray_dir.y = ray->player_dir.y + ray->camera_plane.y * ray->camera_curr_x;
	//store how far the ray has to travel in world space to cross one grid line in the X or Y direction.
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = INT_MAX;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = INT_MAX;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	
	//stepX and stepY determine which direction the ray moves in each axis.
	//If rayDirX > 0, the ray moves right (stepX = +1), otherwise, it moves left (stepX = -1).
	//If rayDirY > 0, the ray moves down (stepY = +1), otherwise, it moves up (stepY = -1).
	//These store the distance from the player's position to the next grid line in both X and Y directions.
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->dist_to_x = (ray->player_pos.x - (double)ray->player_squ.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step = 1;
		ray->dist_to_x = ((double)ray->player_squ.x + 1.0 - ray->player_pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->dist_to_y = (ray->player_pos.y - (double)ray->player_squ.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->dist_to_y = ((double)ray->player_squ.y + 1.0 - ray->player_pos.y) * ray->delta_dist.y;
	}
	//This will hold the final distance from the player to the wall along the ray. Used for rendering the correct height of the wall in perspective projection.
	// double	perp_wall_dist;

}

void	ft_render_walls(t_raycast *raycast)
{
	//number of the pixel used
	int		x;
	bool	hit_wall;

	x = 0;
	hit_wall = false;
	while (x <= WIDTH)
	{
		ft_get_ray(raycast, x);
		while (!hit_wall)
			hit_wall = ft_dda(raycast);

		//ft_put_pixel(cub->image, x, (HEIGHT / 2) - 5, YELLOW);
		x++;
	}

}
