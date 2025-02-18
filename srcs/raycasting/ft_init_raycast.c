#include "../../includes/cub3d.h"

void	ft_init_raycast(t_cub *cub)
{
	cub->raycast->player_pos_x = (double)cub->map->player_squ_x + 0.5;
	cub->raycast->player_pos_y = (double)cub->map->player_squ_y + 0.5;
}
