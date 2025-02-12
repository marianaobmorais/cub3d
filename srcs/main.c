#include "../includes/cub3d.h"

void ft_minimap_init(t_cub *cub)
{
	int		i;
	t_image	*img;

	i = 0;
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		ft_handle_error("malloc: img", cub);
	img->img_ptr = mlx_new_image(cub->mlx, WIDTH / 7, HEIGHT / 7);
	if (!img->img_ptr)
		ft_handle_error("malloc: img->img_ptr", cub);
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		ft_handle_error("malloc: img->addr", cub);
	// while (i <= HEIGHT / 10)
	// {
	// 	ft_put_pixel(img, 0, i, 0xf00edd);
	// 	i++;
	// }
	mlx_put_image_to_window(cub->mlx, cub->window, img->img_ptr, 0, 0);
	//dar free depois
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = (t_cub *) malloc(sizeof(t_cub));
	if (!cub)
		ft_handle_error("malloc: cub", cub);
	if (argc != 2)
		ft_handle_error(strerror(EINVAL), cub);
	ft_loadmap(argv[1], cub);
	printf("Starting cub3D...\n"); //debug
	ft_memset(cub, 0, sizeof(cub));
	cub = ft_init_game(cub);
	if (!cub)
		return (1); //error handler
	printf("game is open\n"); //debug
	ft_print_map(cub->map); //debug

	ft_minimap_init(cub);

	mlx_hook(cub->window, KeyPress, KeyPressMask, ft_key_input, cub);
	mlx_hook(cub->window, DestroyNotify, NoEventMask, ft_close_window, cub);
	mlx_loop(cub->mlx);
	ft_clean_game(cub);
	return (0);
}
