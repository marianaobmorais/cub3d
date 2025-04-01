#include "../../includes/cub3d_bonus.h"

static void	ft_get_sprite_info(t_cub *cub, int i)
{
	//add brief
	double	tmp_pos_x;
	double	tmp_pos_y;
	double	inv; //inverse_determination
	double	transform_x;
	double	transform_y;
	int		sprite_screen_w;
	int		sprite_height;
	int		sprite_start_h;
	int		sprite_end_h;
	int		sprite_width;

	tmp_pos_x = cub->map->sprite[i].pos.x - cub->raycast->player_pos.x;
	tmp_pos_y = cub->map->sprite[i].pos.y - cub->raycast->player_pos.y;

	inv = 1.0 / (cub->raycast->camera_plane.x * cub->raycast->player_dir.y - cub->raycast->player_dir.x * cub->raycast->camera_plane.y);
	
	transform_x = inv * (cub->raycast->player_dir.y * tmp_pos_x - cub->raycast->player_dir.x * tmp_pos_y);
	transform_y = inv * (-cub->raycast->camera_plane.y * tmp_pos_x + cub->raycast->camera_plane.x * tmp_pos_y);
	
	sprite_screen_w = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	
	sprite_height = fabs((int)HEIGHT / transform_y); //using 'transform_y' instead of the real distance prevents fisheye
	sprite_width = sprite_height;
	
	sprite_start_h = -sprite_height / 2 + HEIGHT / 2;
	if (sprite_start_h < 0)
		sprite_start_h = 0;
	sprite_end_h = sprite_height / 2 + HEIGHT / 2;
	if (sprite_end_h >= HEIGHT)
		sprite_end_h = HEIGHT - 1;

	int		sprite_start_w = -sprite_width / 2 + sprite_screen_w;
	if (sprite_start_w < 0)
		sprite_start_w = 0;
	int		sprite_end_w = sprite_width / 2 + sprite_screen_w;
	if (sprite_end_w >= WIDTH)
		sprite_end_w = WIDTH - 1;

	//draw sprite
	int tmp_w = sprite_start_w;
	while (tmp_w < sprite_end_w)
	{
		if (transform_y > 0 && tmp_w > 0 && tmp_w < WIDTH && transform_y < cub->raycast->buffer[tmp_w])
		{

			int texture_w = (int)((tmp_w - (-cub->map->sprite[i].img_a.width / 2 + sprite_screen_w)) * SPRITE_SIZE / cub->map->sprite[i].img_a.width);
			if (texture_w < 0 || texture_w >= SPRITE_SIZE)
				return ;
			int	tmp_h = sprite_start_h;
			while (tmp_h < sprite_end_h)
			{
				//int texture_h = (cub->raycast->texture_pos) % cub->map->sprite[i].img_a.height;
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
