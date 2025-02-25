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

void	ft_init_raycast(t_cub *cub)
{
	cub->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	if (!cub->raycast)
		ft_handle_error("malloc: cub->raycast", cub);
	cub->raycast->player_squ.x = cub->map->player_squ_x;
	cub->raycast->player_squ.y = cub->map->player_squ_y;
	cub->raycast->player_pos.x = (double)cub->map->player_squ_x + 0.5;
	cub->raycast->player_pos.y = (double)cub->map->player_squ_y + 0.5;
	if (cub->map->direction == NORTH)
	{
		cub->raycast->player_dir.x = 0;
		cub->raycast->player_dir.y = -1;
		cub->raycast->camera_plane.x = 0.66;
		cub->raycast->camera_plane.y = 0;
	}
	if (cub->map->direction == SOUTH)
	{
		cub->raycast->player_dir.x = 0;
		cub->raycast->player_dir.y = 1;
		cub->raycast->camera_plane.x = -0.66;
		cub->raycast->camera_plane.y = 0;
	}
	if (cub->map->direction == EAST)
	{
		cub->raycast->player_dir.x = 1;
		cub->raycast->player_dir.y = 0;
		cub->raycast->camera_plane.x = 0;
		cub->raycast->camera_plane.y = 0.66;
	}
	if (cub->map->direction == WEST)
	{
		cub->raycast->player_dir.x = -1;
		cub->raycast->player_dir.y = 0;
		cub->raycast->camera_plane.x = 0;
		cub->raycast->camera_plane.y = -0.66;
	}
	cub->raycast->frame_time = 0;
	cub->raycast->last_frame_time = 0;
}
