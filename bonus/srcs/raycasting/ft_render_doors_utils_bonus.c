#include "../../includes/cub3d_bonus.h"

int	ft_find_door_index(t_cub *cub, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub->map->door_count)
	{
		if (x == (cub->map->door)[i].tile.x
			&& y == (cub->map->door)[i].tile.y)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_open_or_close_door(t_cub *cub)
{
	t_ipoint	tl;
	int			index;

	tl.x = cub->raycast->player_tile.x + (int)round(cub->raycast->player_dir.x);
	tl.y = cub->raycast->player_tile.y + (int)round(cub->raycast->player_dir.y);
	if (tl.x < 0 || tl.x >= cub->map->height
		|| tl.y < 0 || tl.y >= cub->map->width)
		return ;
	if (cub->map->matrix[tl.x][tl.y] == 'D')
	{
		index = ft_find_door_index(cub, tl.x, tl.y);
		if (index < 0)
			return ;
		if (cub->map->door[index].status == CLOSED)
		{
			cub->map->door[index].status = OPENING;
			cub->map->door[index].move = 0;
			cub->map->door[index].timer = 0;
		}
		else if (cub->map->door[index].status == OPEN)
		{
			cub->map->door[index].status = CLOSING;
			cub->map->door[index].timer = 0;
		}
	}
}
