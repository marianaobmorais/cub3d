#include "../../includes/cub3d_bonus.h"

static void	ft_get_sprite_info(t_cub *cub, int i)
{
	//add brief
	double	relative_x;
	double	relative_y;
	double	inv; //inverse_determinate
	double	transform_w;
	double	transform_z;
	int		screen_w;
	int		sprite_height;
	int		sprite_start_h;
	int		sprite_end_h;
	int		sprite_width;

	relative_x = cub->map->sprite[i].pos.x - cub->raycast->player_pos.x;
	relative_y = cub->map->sprite[i].pos.y - cub->raycast->player_pos.y;

	inv = 1.0 / (cub->raycast->player_dir.x * cub->raycast->camera_plane.y - cub->raycast->player_dir.y * cub->raycast->camera_plane.x);
	
	//The camera plane should be used for depth, while player_dir should be used for horizontal position.
	//transform_w tells us how far the sprite is from the center of the screen
	transform_w = inv * (-cub->raycast->player_dir.y * relative_x + cub->raycast->player_dir.x * relative_y);
	//transform_z tells us depth, which affects sprite scaling
	//transform_z (depth) increases, sprite_screen_w decreases, making the sprite appear smaller
	//transform_z decreases, sprite_screen_w increases, making the sprite larger
	transform_z = inv * (cub->raycast->camera_plane.y * relative_x - cub->raycast->camera_plane.x * relative_y);

	printf("transform: w = %lf, z = %lf\n", transform_w, transform_z);//debug
	screen_w = (int)((WIDTH / 2) * (1 + transform_w / transform_z)); //calculates where the sprite should be positioned on screen

	// the apparent height and width of the sprite are inversely proportional to transform_z
	sprite_height = fabs((int)HEIGHT / transform_z); //do we need the fabs function? //using 'transform_y' instead of the real distance prevents fisheye
	sprite_width = sprite_height;
	
	sprite_start_h = -sprite_height / 2 + HEIGHT / 2;
	if (sprite_start_h < 0)
		sprite_start_h = 0;
	sprite_end_h = sprite_height / 2 + HEIGHT / 2;
	if (sprite_end_h >= HEIGHT)
		sprite_end_h = HEIGHT - 1;

	// if (screen_w < 0) //not sure
	// 	screen_w = 0;
	int		sprite_start_w = -sprite_width / 2 + screen_w;
	if (sprite_start_w < 0)
		sprite_start_w = 0;
	int		sprite_end_w = sprite_width / 2 + screen_w;
	if (sprite_end_w >= WIDTH)
		sprite_end_w = WIDTH - 1;

	//draw sprite
	int tmp_w = sprite_start_w;
	while (tmp_w < sprite_end_w)
	{
		//printf("tmp_w = %d, sprite_width: %d, screen_w: %d\n", tmp_w, sprite_width, sprite_screen_w);//debug
		if (transform_z > 0 && tmp_w >= 0 && tmp_w < WIDTH && transform_z < cub->raycast->buffer[tmp_w])
		{
			int texture_w = (int)((tmp_w - (-sprite_width / 2 + screen_w)) * SPRITE_SIZE / sprite_width);
			//printf("texture_w = %d\n", texture_w);//debug
			if (texture_w >= 0 && texture_w < SPRITE_SIZE)
			{
				//printf("within bounds\n");//debug
				int	tmp_h = sprite_start_h;
				while (tmp_h < sprite_end_h)
				{
					int texture_h = (tmp_h - HEIGHT / 2 + sprite_height / 2) * SPRITE_SIZE / sprite_height;//(cub->raycast->texture_pos) % cub->map->sprite[i].img_a.height;
					printf("sprite_width: %d, sprite_height: %d, screen_w: %d\n", sprite_width, sprite_height, screen_w);//debug
					printf("tmp_w = %d, texture_w: %d\n", tmp_w, texture_w);//debug
					printf("tmp_h = %d, texture_h = %d\n", tmp_h, texture_h);//debug
					if (tmp_h >= 0 && tmp_h < SPRITE_SIZE)
					{
						int color = ft_get_pixel_color(&cub->map->sprite[i].img_a, texture_w, texture_h, cub);
						printf("color = %d\n\n", color);//debug
						//if (color != None)
							ft_put_pixel(cub->image, tmp_w, tmp_h, color);
					}
					tmp_h++;
				}
			}
		}
		tmp_w++;
	}
}

// static void	ft_get_sprite_info(t_cub *cub, int i)
// {
// 	//add brief
// 	double	relative_x;
// 	double	relative_y;
// 	double	inv; //inverse_determination
// 	double	transform_pos_x;
// 	double	transform_pos_y;
// 	int		screen_w;
// 	int		sprite_height;
// 	int		sprite_start_h;
// 	int		sprite_end_h;
// 	int		sprite_width;

// 	relative_x = cub->map->sprite[i].pos.x - cub->raycast->player_pos.x;
// 	relative_y = cub->map->sprite[i].pos.y - cub->raycast->player_pos.y;

// 	inv = 1.0 / (cub->raycast->camera_plane.x * cub->raycast->player_dir.y - cub->raycast->player_dir.x * cub->raycast->camera_plane.y);
	
// 	transform_pos_x = inv * (cub->raycast->player_dir.y * relative_x - cub->raycast->player_dir.x * relative_y);
// 	transform_pos_y = inv * (-cub->raycast->camera_plane.y * relative_x + cub->raycast->camera_plane.x * relative_y);
// 	// if (transform_pos_y <= 0)
// 	// 	return ;
// 	//transform_pos_y (depth) increases, sprite_screen_w decreases, making the sprite appear smaller
// 	//transform_pos_y decreases, sprite_screen_w increases, making the sprite larger

// 	printf("transform: x = %lf, y = %lf\n", transform_pos_x, transform_pos_y);//debug
// 	screen_w = (int)((WIDTH / 2) * (1 + transform_pos_x / transform_pos_y)); //calculates where the sprite should be positioned on screen

// 	sprite_height = fabs((int)HEIGHT / transform_pos_y); //using 'transform_y' instead of the real distance prevents fisheye
// 	sprite_width = sprite_height;
	
// 	sprite_start_h = -sprite_height / 2 + HEIGHT / 2;
// 	if (sprite_start_h < 0)
// 		sprite_start_h = 0;
// 	sprite_end_h = sprite_height / 2 + HEIGHT / 2;
// 	if (sprite_end_h >= HEIGHT)
// 		sprite_end_h = HEIGHT - 1;

// 	// if (screen_w < 0) //not sure
// 	// 	screen_w = 0;
// 	int		sprite_start_w = -sprite_width / 2 + screen_w;
// 	if (sprite_start_w < 0)
// 		sprite_start_w = 0;
// 	int		sprite_end_w = sprite_width / 2 + screen_w;
// 	if (sprite_end_w >= WIDTH)
// 		sprite_end_w = WIDTH - 1;

// 	//draw sprite
// 	int tmp_w = sprite_start_w;
// 	while (tmp_w < sprite_end_w)
// 	{
// 		//printf("tmp_w = %d, sprite_width: %d, screen_w: %d\n", tmp_w, sprite_width, sprite_screen_w);//debug
// 		if (transform_pos_y > 0 && tmp_w >= 0 && tmp_w < WIDTH && transform_pos_y < cub->raycast->buffer[tmp_w])
// 		{
// 			int texture_w = (int)((tmp_w - (-sprite_width / 2 + screen_w)) * SPRITE_SIZE / sprite_width);
// 			//printf("texture_w = %d\n", texture_w);//debug
// 			if (texture_w >= 0 && texture_w < SPRITE_SIZE)
// 			{
// 				//printf("within bounds\n");//debug
// 				int	tmp_h = sprite_start_h;
// 				while (tmp_h < sprite_end_h)
// 				{
// 					int texture_h = (tmp_h - HEIGHT / 2 + sprite_height / 2) * SPRITE_SIZE / sprite_height;//(cub->raycast->texture_pos) % cub->map->sprite[i].img_a.height;
// 					printf("sprite_width: %d, sprite_height: %d, screen_w: %d\n", sprite_width, sprite_height, screen_w);//debug
// 					printf("tmp_w = %d, texture_w: %d\n", tmp_w, texture_w);//debug
// 					printf("tmp_h = %d, texture_h = %d\n", tmp_h, texture_h);//debug
// 					if (tmp_h >= 0 && tmp_h < SPRITE_SIZE)
// 					{
// 						int color = ft_get_pixel_color(&cub->map->sprite[i].img_a, texture_w, texture_h, cub);
// 						printf("color = %d\n\n", color);//debug
// 						if (color != None)
// 							ft_put_pixel(cub->image, tmp_w, tmp_h, color);
// 					}
// 					tmp_h++;
// 				}
// 			}
// 		}
// 		tmp_w++;
// 	}
// }

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
