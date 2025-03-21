#include "../../includes/cub3d.h"


/* Now the actual DDA starts. It's a loop that increments the ray with 1 square 
every time, until a wall is hit. Each time, either it jumps a square in the 
x-direction (with stepX) or a square in the y-direction (with stepY), it always 
jumps 1 square at once. If the ray's direction would be the x-direction, the 
loop will only have to jump a square in the x-direction everytime, because the 
ray will never change its y-direction. If the ray is a bit sloped to the 
y-direction, then every so many jumps in the x-direction, the ray will have to 
jump one square in the y-direction. If the ray is exactly the y-direction, it 
never has to jump in the x-direction, etc... */
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
	//check if the ray hit a wall
	if (map->matrix[ray->step_squ.x][ray->step_squ.y] 
		&& map->matrix[ray->step_squ.x][ray->step_squ.y] == '1') //found a wall
		*hit_wall = true;
}
