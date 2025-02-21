#include "../../includes/cub3d.h"

// typedef struct s_raycast
// {
// 	t_dpoint	player_pos;
// 	t_dpoint	player_dir;
// 	t_dpoint	camera_plane;
// 	t_dpoint	ray_dir;
// 	t_dpoint	delta_dist;
// 	t_ipoint	player_squ;
// 	t_ipoint	step;
// 	double		camera_curr_x;
// 	double		frame_time;
// 	double		last_frame_time;
// 	double		dist_to_x;
// 	double		dist_to_y;
// }	t_raycast;

void	ft_init_raycast(t_map *map, t_raycast *raycast)
{
	raycast->player_squ.x = map->player_squ_x;
	raycast->player_squ.y = map->player_squ_y;
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
