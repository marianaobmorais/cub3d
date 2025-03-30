#include "../../includes/cub3d_bonus.h"

void	ft_sort_sprites(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->sprite_count)
	{
		i++;
	}

}

void	ft_render_sprites(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map->sprite_count)
	{
		cub->map->sprite[i].id = i;
		cub->map->sprite[i].dist = (cub->raycast->player_pos.x - cub->map->sprite[i].pos.x) * (cub->raycast->player_pos.x - cub->map->sprite[i].pos.x) + (cub->raycast->player_pos.y - cub->map->sprite[i].pos.y) * (cub->raycast->player_pos.y - cub->map->sprite[i].pos.y);
		cub->map->sprite[i].image = cub->raycast->sprite[i];
		i++;
	}
	ft_sort_sprites(cub->map);
}