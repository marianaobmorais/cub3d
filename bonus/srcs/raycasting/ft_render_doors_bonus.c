#include "../../includes/cub3d_bonus.h"

void	ft_init_doors(t_cub *cub)
{
	int	i;

	i = 0;
	ft_init_xpm_image(cub, &cub->raycast->door_closed, "assets/textures/door/door.xpm");
	ft_init_xpm_image(cub, &cub->raycast->door_open, "assets/textures/door/door14.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[0], "assets/textures/door/door1.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[1], "assets/textures/door/door2.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[2], "assets/textures/door/door3.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[3], "assets/textures/door/door4.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[4], "assets/textures/door/door5.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[5], "assets/textures/door/door6.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[6], "assets/textures/door/door7.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[7], "assets/textures/door/door8.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[8], "assets/textures/door/door9.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[9], "assets/textures/door/door10.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[10], "assets/textures/door/door11.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[11], "assets/textures/door/door12.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[12], "assets/textures/door/door13.xpm");
	ft_init_xpm_image(cub, &cub->raycast->grab_go, "assets/textures/grab_go.xpm");
	while (i < cub->map->door_count)
	{
		(cub->map->door)[i].current = cub->raycast->door_closed;
		i++;
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

void	ft_paint_ray_door(t_cub *cub, int w, t_door door)
{
	int		tex_x, tex_y, y, color;
	int		door_height;
	int		draw_start, draw_end;
	double	step, texture_pos;

	// Altura da projeção
	door_height = (int)(HEIGHT / door.door_dist);

	// Calcular início e fim do desenho vertical
	draw_start = -door_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = door_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

	// Coluna da textura (horizontal)
	tex_x = (int)(door.wall_hit * door.current.width);
	if ((door.door_side == 0 && cub->raycast->ray_dir.x > 0)
		|| (door.door_side == 1 && cub->raycast->ray_dir.y < 0))
		tex_x = door.current.width - tex_x - 1;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= door.current.width)
		tex_x = door.current.width - 1;

	// Passo vertical por pixel
	step = (double)door.current.height / door_height;
	texture_pos = (draw_start - HEIGHT / 2 + door_height / 2) * step;

	// Renderização da coluna
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)texture_pos;
		texture_pos += step;

		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= door.current.height)
			tex_y = door.current.height - 1;

		color = ft_get_pixel_color(&door.current, tex_x, tex_y, cub);
		if (color != IGNORE)
			ft_put_pixel(cub->image, w, y, color);
		y++;
	}
}


void	ft_paint_internal_wall(t_cub *cub, int w)
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
			door->wall_hit = cub->raycast->player_pos.y + door->door_dist * cub->raycast->ray_dir.y;
		else
			door->wall_hit = cub->raycast->player_pos.x + door->door_dist * cub->raycast->ray_dir.x;
		door->wall_hit -= floor(door->wall_hit);
		ft_paint_ray_door(cub, w, *door);
		cub->raycast->door_increment--;
	}
	cub->raycast->hit_door = false;
	cub->raycast->door_increment = -1;
}
