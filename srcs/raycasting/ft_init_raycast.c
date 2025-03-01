#include "../../includes/cub3d.h"

static void	ft_init_north(t_raycast *raycast)
{
	raycast->player_dir.y = 0;
	raycast->player_dir.x = -1;
	raycast->camera_plane.y = 0.66;
	raycast->camera_plane.x = 0;
}

static void	ft_init_south(t_raycast *raycast)
{
	raycast->player_dir.y = 0;
	raycast->player_dir.x = 1;
	raycast->camera_plane.y = -0.66;
	raycast->camera_plane.x = 0;
}

static void	ft_init_east(t_raycast *raycast)
{
	raycast->player_dir.y = 1;
	raycast->player_dir.x = 0;
	raycast->camera_plane.y = 0;
	raycast->camera_plane.x = 0.66;
}

static void	ft_init_west(t_raycast *raycast)
{
	raycast->player_dir.y = -1;
	raycast->player_dir.x = 0;
	raycast->camera_plane.y = 0;
	raycast->camera_plane.x = -0.66;
}

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
		ft_init_north(cub->raycast);
	if (cub->map->direction == SOUTH)
		ft_init_south(cub->raycast);
	if (cub->map->direction == EAST)
		ft_init_east(cub->raycast);
	if (cub->map->direction == WEST)
		ft_init_west(cub->raycast);
	//cub->raycast->frame_time = 0;
	//cub->raycast->last_frame_time = 0;
	cub->raycast->move_speed = 0.3;
}
