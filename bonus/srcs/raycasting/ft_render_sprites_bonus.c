#include "../../includes/cub3d_bonus.h"

static void	ft_get_draw_info(t_sprite *sprite)
{
	(*sprite).start_h = -(*sprite).relative_height / 2 + HEIGHT / 2;
	(*sprite).end_h = (*sprite).relative_height / 2 + HEIGHT / 2;
	(*sprite).start_w = (*sprite).screen_w - (*sprite).relative_width / 2;
	(*sprite).end_w = (*sprite).screen_w + (*sprite).relative_width / 2;
}

static void	ft_draw_sprite(t_cub *cub, t_sprite sprite)
{
	//add brief
	int		tmp_w;
	int		tmp_h;
	int		texture_w;
	int		texture_h;
	int		color;

	tmp_w = (sprite).start_w;
	while (tmp_w < (sprite).end_w)
	{
		if (tmp_w >= 0 && tmp_w < WIDTH && sprite.transform.y < cub->raycast->buffer[tmp_w])
		{
			texture_w = (int)((tmp_w - (sprite).start_w) * (double)sprite.img.width / sprite.relative_width);
			tmp_h = (sprite).start_h;
			while (tmp_h < (sprite).end_h)
			{
				texture_h = (int)((tmp_h - (sprite).start_h) * (double)sprite.img.height / sprite.relative_height);
				if (tmp_h >= 0 && tmp_h < HEIGHT)
				{
					color = ft_get_pixel_color(&sprite.img, texture_w, texture_h, cub);
					if (color == IGNORE)
					{
						color = ft_get_pixel_color(cub->image, tmp_w, tmp_h, cub);
						ft_put_pixel(cub->image, tmp_w, tmp_h, color);
					}
					else
						ft_put_pixel(cub->image, tmp_w, tmp_h, color);
				}
				tmp_h++;
			}
		}
		tmp_w++;
	}
}

static int	ft_get_sprite_info(t_cub *cub, t_sprite *sprite)
{
	//add brief
	double	relative_pos_x;
	double	relative_pos_y;
	double	inv_det;

	relative_pos_x = (*sprite).pos.x - cub->raycast->player_pos.x;
	relative_pos_y = (*sprite).pos.y - cub->raycast->player_pos.y;
	inv_det = 1.0 / (cub->raycast->player_dir.x * cub->raycast->camera_plane.y - cub->raycast->player_dir.y * cub->raycast->camera_plane.x);
	//The camera plane should be used for depth, while player_dir should be used for horizontal position.
	//transform_x tells us how far the sprite is from the center of the screen
	(*sprite).transform.x = inv_det * (-cub->raycast->player_dir.y * relative_pos_x + cub->raycast->player_dir.x * relative_pos_y);
	//transform_y tells us depth, which affects sprite scaling
	//transform_y (depth) increases, sprite_screen_w decreases, making the sprite appear smaller
	//transform_y decreases, sprite_screen_w increases, making the sprite larger
	(*sprite).transform.y = inv_det * (cub->raycast->camera_plane.y * relative_pos_x - cub->raycast->camera_plane.x * relative_pos_y);
	if ((*sprite).transform.y <= 0)
		return (0);
	//screen_w will give the horizontal position on the screen where the sprite will be placed, based on its relative position to the player and the camera's orientation.
	(*sprite).screen_w = (int)((WIDTH / 2) * (1 + (*sprite).transform.x / (*sprite).transform.y)); //calculates where the sprite should be positioned on screen
	// the apparent height and width of the sprite are inversely proportional to transform_z. The larger the value of transform_z, the smaller the sprite appears on the screen and vice-versa
	(*sprite).relative_height = (int)HEIGHT / (*sprite).transform.y; //do we need the fabs function? //using 'transform_y' instead of the real distance prevents fisheye
	(*sprite).relative_width = (*sprite).relative_height;
	return (1);
}

static void	ft_sort_sprites(t_map *map)
{
	//add brief
	//the most distant should go first
	int			i;
	int			count;
	t_sprite	tmp;

	count = map->sprite_count;
	while (count)
	{
		i = 0;
		while (i < count)
		{
			if (map->sprite[i].dist < map->sprite[i + 1].dist)
			{
				tmp = map->sprite[i];
				map->sprite[i] = map->sprite[i + 1];
				map->sprite[i + 1] = tmp;
			}
			i++;
		}
		count--;
	}
}

void	ft_render_sprites(t_cub *cub)
{
	//add brief
	int	i;

	i = 0;
	while (i < cub->map->sprite_count)
	{
		cub->map->sprite[i].dist = (cub->raycast->player_pos.x -
			cub->map->sprite[i].pos.x) * (cub->raycast->player_pos.x -
			cub->map->sprite[i].pos.x) + (cub->raycast->player_pos.y -
			cub->map->sprite[i].pos.y) * (cub->raycast->player_pos.y -
			cub->map->sprite[i].pos.y);
		cub->map->sprite[i].img = cub->raycast->sprite_a[0];
		i++;
	}
	ft_sort_sprites(cub->map);
	i = 0;
	while (i < cub->map->sprite_count)
	{
		if (ft_get_sprite_info(cub, &cub->map->sprite[i]))
		{
			ft_get_draw_info(&cub->map->sprite[i]);
			ft_draw_sprite(cub, cub->map->sprite[i]);
		}
		i++;
	}
}
