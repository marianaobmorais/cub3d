#include "../includes/cub3d.h"

t_image	*ft_init_image(t_cub *game)
{
	game->img->img_ptr = mlx_new_image(game->mlx, PIXEL, PIXEL);
	if (!game->img->img_ptr)
		return (NULL); //error handler
	game->img->bpp = 0;
	game->img->line_len = 0;
	game->img->endian = 0;
	game->img->addr = mlx_get_data_addr(game->img->img_ptr, &game->img->bpp, \
		&game->img->line_len, &game->img->endian);
	if (!game->img->addr)
		return (free(game->img->img_ptr), NULL);
	return (game->img);
}

t_cub	*ft_init_game(void/* t_map *map */)
{
	t_cub	*game;

	game = (t_cub *)malloc(sizeof(t_cub));
	if (!game)
		ft_handle_error("init game", NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_handle_error("mlx init", game);
	game->window = mlx_new_window(game->mlx, PIXEL, PIXEL, "cub3d");
	if (!game->window)
		ft_handle_error("window init", game);
	//game->map = map;
	game->img = (t_image *)malloc(sizeof(t_image));
	if (!game->img)
		ft_handle_error("malloc t_image", game);
	game->img = ft_init_image(game);
	if (!game->img)
		ft_handle_error("image init", game);
	return (game);
}
