#include "../includes/cub3d.h"

void	ft_paint_bg(t_image *img, int y, int color)
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
			ft_paint_bg(img, y, ceiling_color);
		else
			ft_paint_bg(img, y, floor_color);
		y++;
	}
}

void	ft_put_image(t_cub *cub)
{
	if (cub->image->img_ptr)
		mlx_destroy_image(cub->mlx, cub->image->img_ptr);
	cub->image->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image->img_ptr)
		ft_handle_error("malloc: cub->image->img_ptr", cub);
	cub->image->width = WIDTH;
	cub->image->height = HEIGHT;
	cub->image->bpp = 0;
	cub->image->line_len = 0;
	cub->image->endian = 0;
	cub->image->addr = mlx_get_data_addr(cub->image->img_ptr, &cub->image->bpp, &cub->image->line_len, &cub->image->endian);
	if (!cub->image->addr)
		ft_handle_error("malloc: cub->image->addr", cub);
	ft_render_bg(cub->image, cub->map->ceiling_hex, cub->map->floor_hex);
	ft_render_walls(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->image->img_ptr, 0, 0);
}

// void	ft_run_game(t_cub *cub)
// {
// 	ft_init_raycast(cub);
// 	cub->mlx = mlx_init();
// 	if (!cub->mlx)
// 		ft_handle_error("malloc: cub->mlx", cub);
// 	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
// 	if (!cub->window)
// 		ft_handle_error("malloc: cub->window", cub);
// 	cub->image = (t_image *)malloc(sizeof(t_image));
// 	if (!cub->image)
// 		ft_handle_error("malloc: cub->image", cub);
// 	cub->image->img_ptr = NULL;
// 	// cub->minimap = (t_image *)malloc(sizeof(t_image));
// 	// if (!cub->minimap)
// 	// 	ft_handle_error("malloc: cub->minimap", cub);
// 	// cub->minimap->img_ptr = NULL;
// 	//ft_put_image(cub);
// 	//ft_put_minimap(cub);
// }
