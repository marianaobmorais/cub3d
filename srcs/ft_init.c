#include "../includes/cub3d.h"

void	ft_put_pixel(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}

t_image	*ft_init_horizontal(t_cub *cub, t_image *img, int color)
{
	img->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT / 2);
	if (!img->img_ptr)
		return (ft_handle_error("malloc: img->img_ptr", cub), NULL);
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		return (ft_handle_error("malloc: img->addr", cub), NULL);
	int	y;
	int	x;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	return (img);
}

t_cub	*ft_init_game(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_handle_error("malloc: cub->mlx", cub), NULL);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		return (ft_handle_error("malloc: cub->window", cub), NULL);
	cub->ceiling = (t_image *)malloc(sizeof(t_image));
	if (!cub->ceiling)
		return (ft_handle_error("malloc: cub->ceiling", cub), NULL);
	cub->floor = (t_image *)malloc(sizeof(t_image));
	if (!cub->floor)
		return (ft_handle_error("malloc: cub->floor", cub), NULL);
	cub->ceiling = ft_init_horizontal(cub, cub->ceiling, 0xff);
	if (!cub->ceiling)
		return (ft_handle_error("malloc: cub->ceiling", cub), NULL);
	cub->floor = ft_init_horizontal(cub, cub->floor, 0xff00);
	if (!cub->floor)
		return (ft_handle_error("malloc: cub->floor", cub), NULL);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->ceiling->img_ptr, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->floor->img_ptr, 0, HEIGHT / 2);
	return (cub);
}
