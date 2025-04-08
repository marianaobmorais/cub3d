#include "../../includes/cub3d_bonus.h"

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

void	ft_update_doors(t_cub *cub)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < cub->map->door_count)
	{
		door = &cub->map->door[i];
		if (door->status == OPENING)
		{
			door->move += 2;
			if (door->move >= MAX_MOVE)
			{
				door->move = MAX_MOVE;
				door->status = OPEN;
				door->timer = 0;
				door->current = cub->raycast->door_open;
			}
			else
			{
				int index = door->move * (NUM_FRAMES - 1) / MAX_MOVE;
				door->current = cub->raycast->doors[index];
			}
		}
		else if (door->status == CLOSING)
		{
			door->move -= 2;
			if (door->move <= 0)
			{
				door->move = 0;
				door->status = CLOSED;
				door->current = cub->raycast->door_closed;
			}
			else
			{
				int index = door->move * (NUM_FRAMES - 1) / MAX_MOVE;
				door->current = cub->raycast->doors[index];
			}
		}
		else if (door->status == OPEN)
		{
			door->timer += FRAME_DELTA;
			if (door->timer >= 2.0 && (door->tile.x != cub->raycast->player_tile.x || door->tile.y != cub->raycast->player_tile.y))
			{
				door->status = CLOSING;
				door->timer = 0;
			}
		}
		door->timer += FRAME_DELTA;
		i++;
	}
}
