#include "../../includes/cub3d_bonus.h"

static void	ft_draw_sprite(t_cub *cub, t_sprite sprite, int w)
{
	//add brief
	int		h;
	int		texture_w;
	int		texture_h;
	int		color;

	texture_w = (int)((w - sprite.start_w) * (double)sprite.img.width /
		sprite.relative_width);
	h = (sprite).start_h;
	while (h < sprite.end_h)
	{
		texture_h = (int)((h - sprite.start_h) * (double)sprite.img.height /
			sprite.relative_height);
		if (h >= 0 && h < HEIGHT)
		{
			color = ft_get_pixel_color(&sprite.img, texture_w, texture_h, cub);
			if (color == IGNORE)
				color = ft_get_pixel_color(cub->image, w, h, cub);
			ft_put_pixel(cub->image, w, h, color);
		}
		h++;
	}
}

static void	ft_get_draw_info(t_sprite *sprite)
{
	//add brief
	(*sprite).relative_height = (int)HEIGHT / (*sprite).transform.y; //using 'transform_y' instead of the real distance prevents fisheye
	(*sprite).relative_width = (*sprite).relative_height;
	(*sprite).start_h = -(*sprite).relative_height / 2 + HEIGHT / 2;
	(*sprite).end_h = (*sprite).relative_height / 2 + HEIGHT / 2;
	(*sprite).start_w = (*sprite).screen_w - (*sprite).relative_width / 2;
	(*sprite).end_w = (*sprite).screen_w + (*sprite).relative_width / 2;
}

static int	ft_get_sprite_info(t_cub *cub, t_sprite *sprite)
{
	//add brief
	double	relative_pos_x;
	double	relative_pos_y;
	double	inv_det;

	relative_pos_x = (*sprite).pos.x - cub->raycast->player_pos.x;
	relative_pos_y = (*sprite).pos.y - cub->raycast->player_pos.y;
	inv_det = 1.0 / (cub->raycast->player_dir.x * cub->raycast->camera_plane.y
		- cub->raycast->player_dir.y * cub->raycast->camera_plane.x);
	//The camera plane should be used for depth, while player_dir should be used for horizontal position.
	//transform_x tells us how far the sprite is from the center of the screen
	(*sprite).transform.x = inv_det * (-cub->raycast->player_dir.y * 
		relative_pos_x + cub->raycast->player_dir.x * relative_pos_y);
	//transform_y tells us depth, which affects sprite scaling
	//transform_y (depth) increases, sprite_screen_w decreases, making the sprite appear smaller
	//transform_y decreases, sprite_screen_w increases, making the sprite larger
	(*sprite).transform.y = inv_det * (cub->raycast->camera_plane.y *
		relative_pos_x - cub->raycast->camera_plane.x * relative_pos_y);
	if ((*sprite).transform.y <= 0)
		return (0);
	//screen_w will give the horizontal position on the screen where the sprite will be placed, based on its relative position to the player and the camera's orientation.
	(*sprite).screen_w = (int)((WIDTH / 2) * (1 + (*sprite).transform.x /
		(*sprite).transform.y)); //calculates where the sprite should be positioned on screen
	// the apparent height and width of the sprite are inversely proportional to transform_z. The larger the value of transform_z, the smaller the sprite appears on the screen and vice-versa
	return (1);
}

// static void	ft_update_sprites(t_cub *cub)
// {
// 	//add brief
// 	int	i;

// 	if (cub->raycast->time >= 0.4)
// 	{
// 		i = -1;
// 		while (++i < cub->map->sprite_count)
// 		{
// 			if (cub->map->sprite->status)
// 			{
// 				cub->map->sprite[i].img = cub->raycast->sprite_a[0];
// 				cub->map->sprite->status = false;
// 			}
// 			else if (!cub->map->sprite->status && !cub->action)
// 			{
// 				cub->map->sprite[i].img = cub->raycast->sprite_a[1];
// 				cub->map->sprite->status = true;
// 			}
// 			else if (!cub->map->sprite->status && cub->action)
// 			{
// 				cub->map->sprite[i].img = cub->raycast->sprite_b[0];
// 				cub->map->sprite->status = true;
// 			}
// 		}
// 		cub->raycast->time = 0;
// 	}
// 	cub->raycast->time += 0.016;
// }

static void	ft_update_sprites(t_cub *cub)
{
	//update brief
	int	i;

	if (cub->raycast->time >= 0.4)
	{
		i = 0;
		while (i < cub->map->sprite_count)
		{
			if (cub->map->sprite->status)
			{
				cub->map->sprite[i].img = cub->raycast->sprite_still;
				cub->map->sprite->status = false;
			}
			else if (!cub->map->sprite->status)
			{
				if (!cub->action)
					cub->map->sprite[i].img = cub->raycast->sprite_move;
				else
					cub->map->sprite[i].img = cub->raycast->sprite_eat;
				cub->map->sprite->status = true;
			}
			i++;
		}
		cub->raycast->time = 0;
	}
	cub->raycast->time += 0.016;
}

static void	ft_sort_sprites(t_map *map, t_raycast *ray)
{
	//add brief //the most distant should go first //bubble sort
	int			i;
	int			count;
	t_sprite	tmp;

	i = -1;
	while (++i < map->sprite_count)
		map->sprite[i].dist = (ray->player_pos.x - map->sprite[i].pos.x) * 
			(ray->player_pos.x - map->sprite[i].pos.x) + (ray->player_pos.y -
			map->sprite[i].pos.y) * (rayc->player_pos.y - map->sprite[i].pos.y);
	count = map->sprite_count;
	while (count)
	{
		i = -1;
		while (++i < count)
		{
			if (map->sprite[i].dist < map->sprite[i + 1].dist)
			{
				tmp = map->sprite[i];
				map->sprite[i] = map->sprite[i + 1];
				map->sprite[i + 1] = tmp;
			}
		}
		count--;
	}
}

void	ft_render_sprites(t_cub *cub)
{
	//add brief
	int	i;
	int	w;

	ft_sort_sprites(cub->map, cub->raycast);
	ft_update_sprites(cub);
	i = 0;
	while (i < cub->map->sprite_count)
	{
		if (ft_get_sprite_info(cub, &cub->map->sprite[i]))
		{
			ft_get_draw_info(&cub->map->sprite[i]);
			w = sprite[i].start_w;
			while (w < sprite[i].end_w)
			{
				if (w >= 0 && w < WIDTH && sprite.transform.y <
						cub->raycast->buffer[w])
					ft_draw_sprite(cub, cub->map->sprite[i]);
				w++;
			}
		}
		i++;
	}
}
