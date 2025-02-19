#include "../../includes/cub3d.h"

void	ft_init_raycast(t_cub *cub)
{
	cub->raycast->player_pos.x = (double)cub->map->player_squ_x + 0.5;
	cub->raycast->player_pos.y = (double)cub->map->player_squ_y + 0.5;
	if (cub->map->direction == NORTH)
	{
		cub->raycast->player_dir.x = 0;
		cub->raycast->player_dir.y = -1;
	}
	if (cub->map->direction == SOUTH)
	{
		cub->raycast->player_dir.x = 0;
		cub->raycast->player_dir.y = 1;
	}
	if (cub->map->direction == EAST)
	{
		cub->raycast->player_dir.x = 1;
		cub->raycast->player_dir.y = 0;
	}
	if (cub->map->direction == WEST)
	{
		cub->raycast->player_dir.x = -1;
		cub->raycast->player_dir.y = 0;
	}
}
