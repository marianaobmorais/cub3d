#include "../../includes/cub3d_bonus.h"

#define MAX_MOVE 70
#define NUM_FRAMES 8
#define FRAME_DELTA 0.016 // ~60 FPS

void	ft_init_doors(t_cub *cub)
{
	int	i;

	i = 0;
	ft_init_xpm_image(cub, &cub->raycast->door_closed, "assets/textures/door/door.xpm");
	ft_init_xpm_image(cub, &cub->raycast->door_open, "assets/textures/door/door10.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[0], "assets/textures/door/door1.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[1], "assets/textures/door/door2.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[2], "assets/textures/door/door3.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[3], "assets/textures/door/door4.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[4], "assets/textures/door/door5.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[5], "assets/textures/door/door6.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[6], "assets/textures/door/door7.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[7], "assets/textures/door/door8.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[8], "assets/textures/door/door9.xpm");
	while (i < cub->map->door_count)
	{
		(cub->map->door)[i].current = cub->raycast->door_closed;
		i++;
	}
}

int	where_door(t_cub *cub, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub->map->door_count)
	{
		//printf("map door tile --> x %d y %d\n", (cub->map->door)[i].tile.x, (cub->map->door)[i].tile.y);
		if (x == (cub->map->door)[i].tile.x
			&& y == (cub->map->door)[i].tile.y)
			return (i);
		i++;
	}
	return (-1);
}



void	update_doors(t_cub *cub)
{
	int i = 0;
	while (i < cub->map->door_count)
	{
		t_door *door = &cub->map->door[i];

		// === STATUS MACHINE ===
		if (door->status == OPENING)
		{
			door->move += 2;
			if (door->move >= MAX_MOVE)
			{
				door->move = MAX_MOVE;
				door->status = OPEN;
				door->timer = 0;
				door->current = cub->raycast->door_open;
				printf("door [%d] -> OPENING -> OPEN\n", i);
			}
			else
			{
				int index = door->move * (NUM_FRAMES - 1) / MAX_MOVE;
				door->current = cub->raycast->doors[index];
				printf("door [%d] -> OPENING [%d]\n", i, door->move);
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
				printf("door [%d] -> CLOSING -> CLOSED\n", i);
			}
			else
			{
				int index = door->move * (NUM_FRAMES - 1) / MAX_MOVE;
				door->current = cub->raycast->doors[index];
				printf("door [%d] -> CLOSING [%d]\n", i, door->move);
			}
		}
		else if (door->status == OPEN)
		{
			door->timer += FRAME_DELTA;
			if (door->timer >= 5.0)
			{
				door->status = CLOSING;
				door->timer = 0;
				printf("door [%d] -> OPEN -> CLOSING\n", i);
			}
			else
			{
				printf("door [%d] -> OPEN\n", i);
			}
		}
		else if (door->status == CLOSED)
		{
			printf("door [%d] -> CLOSED\n", i);
			// Teste antes de action
			if (door->timer >= 5.0)
				door->status = OPENING;
		}
		door->timer += FRAME_DELTA; // Acumula timer global para todos os estados
		i++;
	}
}


// void	update_doors(t_cub * cub)
// {
// 	int	i;
// 	int	index;

// 	i = 0;
// 	while (i < cub->map->door_count)
// 	{
// 		if ((cub->map->door)[i].timer >= 5.0 && (cub->map->door)[i].status == OPEN)
// 		{
// 			(cub->map->door)[i].status = CLOSING;
// 			(cub->map->door)[i].timer = 0;
// 			printf("door [%d] -> OPEN -> CLOSING\n", i);
// 		}
// 		else if ((cub->map->door)[i].move >= 70)
// 		{
// 			(cub->map->door)[i].status = OPEN;
// 			(cub->map->door)[i].current = cub->raycast->door_open;
// 			printf("door [%d] -> OPENING -> OPEN\n", i);
// 		}
// 		else if ((cub->map->door)[i].move < -70 && (cub->map->door)[i].status == CLOSING)
// 		{
// 			(cub->map->door)[i].status = CLOSED;
// 			(cub->map->door)[i].current = cub->raycast->door_closed;
// 			printf("door [%d] -> CLOSING -> CLOSED\n", i);
// 		}

// 		if ((cub->map->door)[i].status == CLOSED)
// 		{
// 			if ((cub->map->door)[i].timer >= 5.0) //test
// 				(cub->map->door)[i].status = OPENING; //test
// 			printf("door [%d] -> CLOSED\n", i); //(cub->map->door)[i].current = cub->hud->door;
// 		}
// 		else if ((cub->map->door)[i].status == OPEN)
// 		{
// 			(cub->map->door)[i].timer++;
// 			printf("door [%d] -> OPEN\n", i); //(cub->map->door)[i].current = cub->hud->door;
// 		}
// 		else if ((cub->map->door)[i].status == OPENING /* || action?? */)
// 		{
// 			index = (cub->map->door)[i].move / 10;
// 			(cub->map->door)[i].current = cub->raycast->doors[index];
// 			(cub->map->door)[i].move++;
// 			printf("door [%d] -> OPENING [%d]\n", i, (cub->map->door)[i].move); //(cub->map->door)[i].current = cub->hud->door;
// 		}
// 		else if ((cub->map->door)[i].status == CLOSING /* || action?? */)
// 		{
// 			index = (cub->map->door)[i].move / 10;
// 			(cub->map->door)[i].current = cub->raycast->doors[index];
// 			(cub->map->door)[i].move--;
// 			printf("door [%d] -> CLOSING [%d]\n", i, (cub->map->door)[i].move); //(cub->map->door)[i].current = cub->hud->door;
// 		}
// 		(cub->map->door)[i].timer += 0.016;//test
// 		printf("timer-> %f\n",(cub->map->door)[i].timer);
// 		i++;
// 	}
// }

void	paint_door(t_cub *cub, int draw_left, int x, int draw_start, int draw_end, int door_width, int door_height)
{
	int			y;
	int			color;
	int			color_default;
	t_ipoint	tex;

	tex.x = (int) ((x - draw_left) * (double) cub->hud->door.width / door_width);
	y = draw_start;
	while (y < draw_end)
	{
		tex.y = (int) ((y - draw_start) * (double) cub->hud->door.height / door_height);
		if (y >= 0 && y < HEIGHT)
		{
			color = ft_get_pixel_color(&cub->hud->door, tex.x, tex.y, cub);
			if (color == IGNORE)
			{
				color_default = ft_get_pixel_color(cub->image, x, y, cub);
				ft_put_pixel(cub->image, x, y, color_default);
			}
			else
				ft_put_pixel(cub->image, x, y, color);
		}
		y++;
	}
}

void	ft_render_door(t_cub *cub, t_door door)
{
	t_dpoint	relative;
	t_dpoint	transform;
	double		inv;
	int			screen_x;
	int			door_height;
	int			door_width;
	int			draw_start;
	int			draw_end;
	int			draw_left;
	int			draw_right;
	int			x;

	relative.x = door.tile.x + 0.5 - cub->raycast->player_pos.x;
	relative.y = door.tile.y + 0.5 - cub->raycast->player_pos.y;

	inv = 1.0 / (cub->raycast->camera_plane.x * cub->raycast->player_dir.y - \
		cub->raycast->camera_plane.y * cub->raycast->player_dir.x);
	
	transform.x = inv * (cub->raycast->player_dir.y * relative.x - \
		cub->raycast->player_dir.x * relative.y); //horizontal
	// transform.y = inv * (-cub->raycast->camera_plane.y * relative.x + 
	// 	cub->raycast->camera_plane.x * relative.y); //profundidade
	transform.y = cub->raycast->perp_wall_dist;

	if (transform.y <= 0) //atras do player
		return ;

	screen_x = (int) ((WIDTH / 2) * (1 + transform.x / transform.y)); //coordenada na tela

	door_height = abs((int) (HEIGHT / transform.y));
	draw_start = -door_height / 2 + HEIGHT / 2;
	draw_end = door_height / 2 + HEIGHT / 2;

	door_width = abs((int) (HEIGHT / transform.y));
	draw_left = screen_x - door_width / 2;
	draw_right = screen_x + door_width / 2;

	x = draw_left;
	while (x < draw_right)
	{
		if (x >= 0 && x < WIDTH && transform.y < cub->raycast->buffer[x])
			paint_door(cub, draw_left, x, draw_start, draw_end, door_width, door_height);
		x++;
	}
}

void	ft_paint_ray_door(t_cub *cub, int w, t_image texture,
	double dist, int side, double wall_hit)
{
	int		tex_x;
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
