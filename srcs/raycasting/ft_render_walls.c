#include "../../includes/cub3d.h"

void	ft_get_ray_size(t_raycast *raycast, int x)
{
	//is the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
	//done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1
	double	ray_dir_x;
	double	ray_dir_y;

	raycast.camera_curr_x = 2 * (double)(x / WIDTH) - 1; //or (x / (double)WIDTH)?
	//the direction of the ray can be calculated as was explained earlier: as the sum of the direction vector, and a part of the plane vector.
	//This has to be done both for the x and y coordinate of the vector (since adding two vectors is adding their x-coordinates, and adding their y-coordinates).
	raycast->ray_dir.x = raycast->player_dir.x + raycast->camera_plane.x * raycast->camera_curr_x;
	raycast->ray_dir.y = raycast->player_dir.y + raycast->camera_plane.y * raycast->camera_curr_x;
	if (raycast->ray_dir.x == 0)
		raycast->delta_dir.x = INT_MAX;
	else
		raycast->delta_dir.x = fabs(1 / raycast->ray_dir.x);
	if (raycast->ray_dir.y == 0)
		raycast->delta_dir.y = INT_MAX;
	else
		raycast->delta_dir.y = fabs(1 / raycast->ray_dir.y)
}

void	ft_render_walls(t_raycast *raycast, t_map *map)
{
	//number of the pixel used
	int	x;

	x = 0;
	while (x <= WIDTH)
	{
		ft_get_ray_size(raycast, x);
		ft_dda(raycast);

		//ft_put_pixel(cub->image, x, (HEIGHT / 2) - 5, YELLOW);
		x++;
	}

}
