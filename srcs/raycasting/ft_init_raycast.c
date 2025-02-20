#include "../../includes/cub3d.h"

void	ft_init_raycast(t_map *map, t_raycast *raycast)
{
	raycast->player_pos.x = (double)map->player_squ_x + 0.5;
	raycast->player_pos.y = (double)map->player_squ_y + 0.5;
	if (map->direction == NORTH)
	{
		raycast->player_dir.x = 0;
		raycast->player_dir.y = -1;
	}
	if (map->direction == SOUTH)
	{
		raycast->player_dir.x = 0;
		raycast->player_dir.y = 1;
	}
	if (map->direction == EAST)
	{
		raycast->player_dir.x = 1;
		raycast->player_dir.y = 0;
	}
	if (map->direction == WEST)
	{
		raycast->player_dir.x = -1;
		raycast->player_dir.y = 0;
		raycast->camera_plane.x = 0;
		raycast->camera_plane.y = 0.66;
	}
	raycast->frame_time = 0;
	raycast->last_frame_time = 0;
}
