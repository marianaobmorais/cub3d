#include "../../includes/cub3d_bonus.h"

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
