#include "../../includes/cub3d.h"

int	ft_get_pixel_color(int x, int y, t_image *source)
{
	char	*addr;
	char	*dst;
	int		offset;

	addr = source->addr ;
	offset = (y * source->line_len) + (x * (source->bpp / 8));
	dst = offset + addr;
	return (*(unsigned int *)dst);
}

void	ft_paint_source_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y)
{
	int	source_color;
	int	default_color;
	int	y;
	int	x;

	y = 0;
	while (y < source->height)
	{
		x = 0;
		while (x < source->width)
		{
			source_color = ft_get_pixel_color(x, y, source);
			if (source_color == 0xFFFFFF) //color to ignore
			{
				default_color = ft_get_pixel_color(x + pos_x, y + pos_y, cub->image);
				ft_put_pixel(cub->hud->img, x + pos_x, y + pos_y, default_color);
			}
			else
				ft_put_pixel(cub->hud->img, x + pos_x, y + pos_y, source_color);
			x++;
		}
		y++;
	}
}

void	ft_put_hud(t_cub *cub)
{
	if (cub->hud->img->img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->img->img_ptr);

	cub->hud->img->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->hud->img->img_ptr)
		ft_handle_error("malloc: hud->img_ptr", cub);

	cub->hud->img->bpp = 0;
	cub->hud->img->line_len = 0;
	cub->hud->img->endian = 0;
	cub->hud->img->addr = mlx_get_data_addr(cub->hud->img->img_ptr, \
		&cub->hud->img->bpp, &cub->hud->img->line_len, &cub->hud->img->endian);
	if (!cub->hud->img->addr)
		ft_handle_error("malloc: img->addr", cub);	

	ft_paint_source_on_hud(cub, cub->image, 0, 0); //paint main image
	ft_paint_source_on_hud(cub, cub->hud->watch, 0, 0); //paint watch image for minimap
	ft_paint_minimap_on_hud(cub); //minimap
	//bag with bread
	//hand holding bread
	//action bread another img
	mlx_put_image_to_window(cub->mlx, cub->window, cub->hud->img->img_ptr, 0, 0);
}
