#include "../../includes/cub3d.h"

bool	ft_dda(t_raycast *ray)
{
	bool	is_wall;

	is_wall = false;
	if (ray->dist_to_x < ray->dist_to_y)
	{
		ray->dist_to_x += ray->delta_dist.x;

	}

	return ;
}