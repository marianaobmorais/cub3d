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
