#include "../includes/cub3d.h"

void	ft_colorize(t_image *img, int y, int color)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ft_put_pixel(img, x, y, color);
		x++;
	}
}

void	ft_render_bg(t_image *img, int ceiling_color, int floor_color)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y <= HEIGHT / 2)
			ft_colorize(img, y, ceiling_color);
		else
			ft_colorize(img, y, floor_color);
		y++;
	}
}

void	ft_render_walls(t_image *img, t_map *map)
{
	(void)img;
	(void)map;
	//int	factor; //aka multiplier
	int	x; //number of the pixel used

	x = 0;
	while (x < WIDTH)
	{
		//factor = 2 * (x / WIDTH) - 1;

		ft_put_pixel(img, x, (HEIGHT / 2) - 5, YELLOW);
		x++;
	}

}

void	ft_put_image(t_cub *cub)
{
	if (cub->image->img_ptr)
		mlx_destroy_image(cub->mlx, cub->image->img_ptr);
	cub->image->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image->img_ptr)
		ft_handle_error("malloc: cub->image->img_ptr", cub);
	cub->image->bpp = 0;
	cub->image->line_len = 0;
	cub->image->endian = 0;
	cub->image->addr = mlx_get_data_addr(cub->image->img_ptr, &cub->image->bpp, &cub->image->line_len, &cub->image->endian);
	if (!cub->image->addr)
		ft_handle_error("malloc: cub->image->addr", cub);
	ft_render_bg(cub->image, cub->map->ceiling_hex, cub->map->floor_hex);
	ft_render_walls(cub->image, cub->map);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->image->img_ptr, 0, 0);
}

void ft_put_minimap(t_cub *cub)
{
	if (cub->minimap->img_ptr)
		mlx_destroy_image(cub->mlx, cub->minimap->img_ptr);
	cub->minimap->img_ptr = mlx_new_image(cub->mlx, WIDTH / 7, HEIGHT / 7);
	if (!cub->minimap->img_ptr)
		ft_handle_error("malloc: img->img_ptr", cub);
	cub->minimap->bpp = 0;
	cub->minimap->line_len = 0;
	cub->minimap->endian = 0;
	cub->minimap->addr = mlx_get_data_addr(cub->minimap->img_ptr, &cub->minimap->bpp, &cub->minimap->line_len, &cub->minimap->endian);
	if (!cub->minimap->addr)
		ft_handle_error("malloc: img->addr", cub);
	//ft_render_minimap();
	mlx_put_image_to_window(cub->mlx, cub->window, cub->minimap->img_ptr, 0, 0);
}


t_cub	*ft_init_game(t_cub *cub)
{
	cub->image = NULL;
	cub->minimap = NULL;
	cub->raycast = NULL;
	cub->window = NULL;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_handle_error("malloc: cub->mlx", cub), NULL);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		return (ft_handle_error("malloc: cub->window", cub), NULL);
	cub->image = (t_image *)malloc(sizeof(t_image));
	if (!cub->image)
		ft_handle_error("malloc: cub->image", cub);
	cub->image->img_ptr = NULL;
	cub->minimap = (t_image *)malloc(sizeof(t_image));
	if (!cub->minimap)
		ft_handle_error("malloc: cub->minimap", cub);
	cub->minimap->img_ptr = NULL;
	cub->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	if (!cub->raycast)
		ft_handle_error("malloc: cub->raycast", cub);
	ft_init_raycast(cub);
	ft_put_image(cub);
	ft_put_minimap(cub);
	return (cub);
}
