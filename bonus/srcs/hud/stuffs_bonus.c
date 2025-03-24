#include "../../includes/cub3d_bonus.h"

void	ft_paint_action_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y)
{
	int	source_color;
	int	default_color;
	int	y;
	int	x;
	pos_x = 200;
	pos_y = 400;
	
	if (cub->hud->img->img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->img->img_ptr);
	cub->hud->img->img_ptr = mlx_new_image(cub->mlx, cub->hud->breadcrumbs->width, cub->hud->breadcrumbs->height);
	if (!cub->hud->img->img_ptr)
		ft_handle_error("malloc: hud->img_ptr", cub);
	cub->hud->img->bpp = 0;
	cub->hud->img->line_len = 0;
	cub->hud->img->endian = 0;
	cub->hud->img->addr = mlx_get_data_addr(cub->hud->img->img_ptr, 
		&cub->hud->img->bpp, &cub->hud->img->line_len, &cub->hud->img->endian);
	if (!cub->hud->img->addr)
		ft_handle_error("malloc: img->addr", cub);

	y = 0;
	while (y < source->height)
	{
		x = 0;
		while (x < source->width)
		{
			source_color = ft_get_pixel_color(source, x, y, cub);
			if (source_color == IGNORE) //color to ignore
			{
				default_color = ft_get_pixel_color(cub->image, x + pos_x, y + pos_y, cub);
				ft_put_pixel(cub->hud->img, x, y, default_color);
			}
			else
				ft_put_pixel(cub->hud->img, x, y, source_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->window, cub->hud->img->img_ptr, pos_x, pos_y);
	usleep(5000);
}

void	draw_line_minimap(t_cub *cub, int x1, int y1, int x2, int y2, int color)
{
	//test
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (x1 != x2 || y1 != y2)
	{
		ft_put_pixel(cub->image, x1, y1, color);
		int e2 = err * 2;
		if (e2 > -dy) { err -= dy; x1 += sx; }
		if (e2 < dx) { err += dx; y1 += sy; }
	}
}

void	ft_render_fov_minimap(t_cub *cub)
{
	//test
	int	i;
	int	map_x;
	int	map_y;
	int	player_x;
	int	player_y;

	i = 0;
	while (i < WIDTH)
	{
		map_x = cub->hud->ray_hits[i].x * MINIMAP_SCALE_X;
		map_y = cub->hud->ray_hits[i].y * MINIMAP_SCALE_Y;
		player_x = cub->raycast->player_squ.x * MINIMAP_SCALE_X;
		player_y = cub->raycast->player_squ.y * MINIMAP_SCALE_Y;
		draw_line_minimap(cub, player_x + 9, player_y + 4, map_x + 9, map_y + 4, RED);
		printf("line"); //debug
		i += 10;
	}
}

// void	ft_door(t_cub *cub, int height, int width)
// {
// 	//test
// 	int	y;
// 	int	x;
// 	int color;
// 	int blend;

// 	y = 0;
// 	while (y < height)
// 	{
// 		x = 0;
// 		while (x < width)
// 		{
// 			//ft_put_pixel(cub->hud->img, x + 17, y + 39, color);
// 			color = ft_get_pixel_color(x + 200, y + 200, cub->image);
// 			blend = ft_blendcolors(color, 0xADD8E6, 0.5);
// 			ft_put_pixel(cub->image, x + 200, y + 200, blend);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	ft_door(t_cub *cub, t_image *source, int pos_x, int pos_y)
{
	//test
	int	source_color;
	int	blend;
	int default_color;
	int	y;
	int	x;

	y = 0;
	while (y < source->height)
	{
		x = 0;
		while (x < source->width)
		{
			source_color = ft_get_pixel_color(source, x, y, cub);
			if (source_color == 0x00FFFF) //color to ignore
			{
				default_color = ft_get_pixel_color(cub->image, x + pos_x, y + pos_y, cub);
				blend = ft_blendcolors(default_color, 0x00FFF0, 0.5);
				ft_put_pixel(cub->image, x + pos_x, y + pos_y, blend);
			}
			else
				ft_put_pixel(cub->image, x + pos_x, y + pos_y, source_color);
			x++;
		}
		y++;
	}
}

void	ft_hextoarray(int hex, unsigned char *rgb)
{
	//brief
	rgb[0] = (hex >> 16) & 0xFF;
	rgb[1] = (hex >> 8) & 0xFF;
	rgb[2] = hex & 0xFF;
}
