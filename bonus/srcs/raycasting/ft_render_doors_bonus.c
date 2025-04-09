#include "../../includes/cub3d_bonus.h"

void	ft_init_doors(t_cub *cub)
{
	int	i;

	i = 0;
	ft_init_xpm_image(cub, &cub->raycast->door_closed, "assets/door/door.xpm");
	ft_init_xpm_image(cub, &cub->raycast->door_open, "assets/door/door14.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[0], "assets/door/door1.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[1], "assets/door/door2.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[2], "assets/door/door3.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[3], "assets/door/door4.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[4], "assets/door/door5.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[5], "assets/door/door6.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[6], "assets/door/door7.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[7], "assets/door/door8.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[8], "assets/door/door9.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[9], "assets/door/door10.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[10], "assets/door/door11.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[11], "assets/door/door12.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[12], "assets/door/door13.xpm");
	ft_init_xpm_image(cub, &cub->raycast->grab_go, "assets/door/grab_go.xpm");
	while (i < cub->map->door_count)
	{
		(cub->map->door)[i].current = cub->raycast->door_closed;
		i++;
	}
}

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

static void	ft_paint_internal_wall(t_cub *cub, int w)
{
	t_ipoint	tile;
	char		**matrix;

	tile = cub->raycast->step_tile;
	matrix = cub->map->matrix;
	if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x < 0
		&& tile.x + 1 < cub->map->height && matrix[tile.x + 1][tile.y] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go); // face norte
	if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x >= 0
		&& tile.x > 0 && matrix[tile.x - 1][tile.y] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go); // face sul
	if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y < 0
		&& tile.y + 1 < cub->map->width && matrix[tile.x][tile.y + 1] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go); // face oeste
	if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y >= 0
		&& tile.y > 0 && matrix[tile.x][tile.y - 1] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go); // face leste
}

void	ft_render_doors(t_cub *cub, int w)
{
	int		index;
	t_door	*door;

	ft_paint_internal_wall(cub, w);
	while (cub->raycast->door_increment > -1)
	{
		index = ft_find_door_index(cub, \
			cub->raycast->doors_found[cub->raycast->door_increment].x, \
			cub->raycast->doors_found[cub->raycast->door_increment].y);
		door = &cub->map->door[index];
		if (door->door_side == 0)
			door->wall_hit = cub->raycast->player_pos.y + door->door_dist * \
			cub->raycast->ray_dir.y;
		else
			door->wall_hit = cub->raycast->player_pos.x + door->door_dist * \
			cub->raycast->ray_dir.x;
		door->wall_hit -= floor(door->wall_hit);
		ft_paint_ray_door(cub, w, *door);
		cub->raycast->door_increment--;
	}
	cub->raycast->hit_door = false;
	cub->raycast->door_increment = -1;
}
