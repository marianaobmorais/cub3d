#include "../../includes/cub3d_bonus.h"

// void	ft_paint_ray(t_cub *cub, int window_w, t_image texture)
// {
// 	double			step;
// 	int				texture_w;
// 	int				texture_h;
// 	int				tmp_h;
// 	unsigned int	color;

// 	texture_w = (int)(cub->raycast->wall_hit_value * (double)texture.width);
// 	if (cub->raycast->hit_side == SOUTH)
// 		texture_w = texture.width - texture_w - 1;
// 	if (cub->raycast->hit_side == EAST)
// 		texture_w = texture.width - texture_w - 1;
// 	texture_w = texture_w % texture.width;
// 	step = 1.0 * ((double) texture.height / cub->raycast->wall_height);
// 	cub->raycast->texture_pos = (cub->raycast->wall_start - HEIGHT / 2
// 			+ cub->raycast->wall_height / 2) * step;
// 	tmp_h = cub->raycast->wall_start;
// 	while (tmp_h <= cub->raycast->wall_end)
// 	{
// 		texture_h = (int)cub->raycast->texture_pos % texture.height;
// 		cub->raycast->texture_pos += step;
// 		color = ft_get_pixel_color(&texture, texture_w, texture_h, cub);
// 		ft_put_pixel(cub->image, window_w, tmp_h, color);
// 		tmp_h++;
// 	}
// }


static void	ft_get_sprite_info(t_cub *cub, int i)
{
	//add brief
	double	tmp_pos_x;
	double	tmp_pos_y;
	double	invert;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_w;
	int		sprite_height;
	int		sprite_start_h;
	int		sprite_end_h;

	tmp_pos_x = cub->map->sprite[i].pos.x - cub->raycast->player_pos.x;
	tmp_pos_y = cub->map->sprite[i].pos.y - cub->raycast->player_pos.y;
	invert = 1.0 / (cub->raycast->camera_plane.x * cub->raycast->player_dir.y - cub->raycast->player_dir.x * cub->raycast->camera_plane.y);
	transform_x = invert * (cub->raycast->player_dir.y * tmp_pos_x - cub->raycast->player_dir.x * tmp_pos_y);
	transform_y = invert * (-cub->raycast->camera_plane.y * tmp_pos_x + cub->raycast->camera_plane.x * tmp_pos_y);
	sprite_screen_w = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_height = fabs((int)HEIGHT / transform_y); //using 'transform_y' instead of the real distance prevents fisheye
	sprite_start_h = -sprite_height / 2 + HEIGHT / 2;
	if (sprite_start_h < 0)
		sprite_start_h = 0;
	sprite_end_h = sprite_height / 2 + HEIGHT / 2;
	if (sprite_end_h >= HEIGHT)
		sprite_end_h = HEIGHT - 1;

	int		sprite_width = fabs((int)HEIGHT / (transform_y));
	int		sprite_start_w = -sprite_width / 2 + sprite_screen_w;
	if (sprite_start_w < 0)
		sprite_start_w = 0;
	int		sprite_end_w = sprite_width / 2 + sprite_screen_w;
	if (sprite_end_w >= WIDTH)
		sprite_end_w = WIDTH - 1;

	int tmp_w = sprite_start_w;
	while (tmp_w < sprite_end_w)
	{
		printf("Z-buffer[%d] = %f, Transform Y = %f\n", tmp_w, cub->raycast->buffer[tmp_w], transform_y);//debug
		printf("Sprite screen w: %d, start: %d, end: %d\n", sprite_screen_w, sprite_start_w, sprite_end_w); //debug
		printf("Sprite %d: Transform Y = %f\n", i, transform_y);
		double	step = 1.0 * ((double) cub->map->sprite[i].img_a.height / cub->map->sprite[i].img_a.height);
		int		texture_w = (int)(cub->raycast->wall_hit_value * (double)cub->map->sprite[i].img_a.width);
		
		if (transform_y > 0 && tmp_w > 0 && tmp_w < WIDTH && transform_y < cub->raycast->buffer[tmp_w])
		{
			//printf("entered here\n"); //debug
			int	tmp_h = sprite_start_h;
			while (tmp_h < sprite_end_h)
			{
				int texture_h = (int)(cub->raycast->texture_pos) % cub->map->sprite[i].img_a.height;
				cub->raycast->texture_pos += step;
				int color = ft_get_pixel_color(&cub->map->sprite[i].img_a, texture_w, texture_h, cub);
				ft_put_pixel(cub->image, tmp_w, tmp_h, color);
				tmp_h++;
			}
		}
		tmp_w++;
	}
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
	int	j;

	i = 0;
	j = 0;
	while (i < cub->map->sprite_count)
	{
		cub->map->sprite[i].dist = (cub->raycast->player_pos.x - cub->map->sprite[i].pos.x) * (cub->raycast->player_pos.x - cub->map->sprite[i].pos.x) + (cub->raycast->player_pos.y - cub->map->sprite[i].pos.y) * (cub->raycast->player_pos.y - cub->map->sprite[i].pos.y);
		if (j == 1) //should be 3, but temporarily it's 1
			j = 0;
		cub->map->sprite[i].img_a = cub->raycast->sprite_a[j];
		cub->map->sprite[i].img_b = cub->raycast->sprite_b[j];
		i++;
		j++;
	}
	ft_sort_sprites(cub->map);
	i = 0;
	while (i < cub->map->sprite_count)
	{
		ft_get_sprite_info(cub, i);
		i++;
	}
}
