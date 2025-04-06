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
			if (door->timer >= 2.0)
			{
				door->status = CLOSING;
				door->timer = 0;
			}
		}
		door->timer += FRAME_DELTA;
		i++;
	}
}

void	ft_paint_ray_door(t_cub *cub, int w, t_image texture,
	double dist, int side, double wall_hit)
{
	int		tex_x; //usar t_ipoint
	int		tex_y;
	int		draw_start;
	int		draw_end;
	double	texture_pos;
	double	step;
	int		door_height;
	int		y;
	int		color;

	door_height = (int)(HEIGHT / dist);
	draw_start = -door_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = door_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

	// tex_x (coluna da textura)
	tex_x = (int)(wall_hit * texture.width);
	if ((side == 0 && cub->raycast->ray_dir.x > 0) || (side == 1 && cub->raycast->ray_dir.y < 0))
		tex_x = texture.width - tex_x - 1;
	tex_x %= texture.width;

	// passo vertical por pixel
	step = (double)texture.height / door_height;
	texture_pos = (draw_start - HEIGHT / 2 + door_height / 2) * step;

	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)texture_pos % texture.height;
		texture_pos += step;

		color = ft_get_pixel_color(&texture, tex_x, tex_y, cub);
		if (color != IGNORE)
			ft_put_pixel(cub->image, w, y, color);
		y++;
	}
}

void	ft_render_doors(t_cub *cub, int w)
{
	int		index;
	t_door	*door;
	double	wall_hit;
	double	side;
	double	dist;

	while (cub->raycast->door_increment > -1)
	{
		index = ft_find_door_index(cub, \
			cub->raycast->doors_found[cub->raycast->door_increment].x, \
			cub->raycast->doors_found[cub->raycast->door_increment].y);
		door = &cub->map->door[index];
		dist = door->door_dist;
		side = door->door_side;
		if (side == 0)
			wall_hit = cub->raycast->player_pos.y + dist * cub->raycast->ray_dir.y;
		else
			wall_hit = cub->raycast->player_pos.x + dist * cub->raycast->ray_dir.x;
		wall_hit -= floor(wall_hit);
		ft_paint_ray_door(cub, w, door->current, dist, side, wall_hit);
		cub->raycast->door_increment--;
	}
	cub->raycast->hit_door = false;
	cub->raycast->door_increment = -1;
}
