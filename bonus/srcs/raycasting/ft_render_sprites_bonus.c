#include "../../includes/cub3d_bonus.h"

static void	ft_get_sprite_info(t_cub *cub, int i)
{
	//add brief
	double	relative_x;
	double	relative_y;
	double	inv; //inverse_determinant
	double	transform_w; //move to struct
	double	transform_z; //move to struct
	int		screen_w;
	int		relative_height;
	int		sprite_start_h;
	int		sprite_end_h;
	int		sprite_width;

	relative_x = cub->map->sprite[i].pos.x - cub->raycast->player_pos.x;
	relative_y = cub->map->sprite[i].pos.y - cub->raycast->player_pos.y;
	inv = 1.0 / (cub->raycast->player_dir.x * cub->raycast->camera_plane.y - cub->raycast->player_dir.y * cub->raycast->camera_plane.x);
	//The camera plane should be used for depth, while player_dir should be used for horizontal position.
	//transform_x tells us how far the sprite is from the center of the screen
	transform_w = inv * (-cub->raycast->player_dir.y * relative_x + cub->raycast->player_dir.x * relative_y);
	//transform_y tells us depth, which affects sprite scaling
	//transform_y (depth) increases, sprite_screen_w decreases, making the sprite appear smaller
	//transform_y decreases, sprite_screen_w increases, making the sprite larger
	transform_z = inv * (cub->raycast->camera_plane.y * relative_x - cub->raycast->camera_plane.x * relative_y);
	if (transform_z <= 0)
		return ;
	//screen_w will give the horizontal position on the screen where the sprite will be placed, based on its relative position to the player and the camera's orientation.
	screen_w = (int)((WIDTH / 2) * (1 + transform_w / transform_z)); //calculates where the sprite should be positioned on screen
	// the apparent height and width of the sprite are inversely proportional to transform_z. The larger the value of transform_z, the smaller the sprite appears on the screen and vice-versa
	relative_height = (int)HEIGHT / transform_z; //do we need the fabs function? //using 'transform_y' instead of the real distance prevents fisheye
	sprite_width = relative_height;
	sprite_start_h = -relative_height / 2 + HEIGHT / 2;
	sprite_end_h = relative_height / 2 + HEIGHT / 2;
	int		sprite_start_w = screen_w - sprite_width / 2;
	int		sprite_end_w = screen_w + sprite_width / 2;


	//draw sprite
	int tmp_w = sprite_start_w;
	while (tmp_w < sprite_end_w)
	{
		//printf("tmp_w = %d, sprite_width: %d\n", tmp_w, sprite_width);//debug
		if (tmp_w >= 0 && tmp_w < WIDTH && transform_z < cub->raycast->buffer[tmp_w])
		{
			int	texture_w = (int)((tmp_w - sprite_start_w) * (double)cub->map->sprite[i].img_a.width / sprite_width);
			//printf("texture_w = %d\n", texture_w);//debug		
			int	tmp_h = sprite_start_h;
			while (tmp_h < sprite_end_h)
			{
				int	texture_h = (int)((tmp_h - sprite_start_h) * (double)cub->map->sprite[i].img_a.height / sprite_height);
				if (tmp_h >= 0 && tmp_h < HEIGHT /* SPRITE_SIZE */)
				{
					int color = ft_get_pixel_color(&cub->map->sprite[i].img_a, texture_w, texture_h, cub);
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
		cub->map->sprite[i].img_b = cub->raycast->sprite_b[j]; //review logic
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
