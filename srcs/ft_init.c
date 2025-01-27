#include "../includes/cub3d.h"

t_image	*ft_init_image(t_game *game) //init image for each element? ceiling/floor/walls
{
	game->img->img_ptr = mlx_new_image(game->mlx, WIDHT, HEIGHT);
	if (!game->img->img_ptr)
		return (NULL); //error handler
	game->img->bpp = 0;
	game->img->line_len = 0;
	game->img->endian = 0;
	game->img->addr = mlx_get_data_addr(game->img->img_ptr, &game->img->bpp, &game->img->line_len, &game->img->endian);
	if (!game->img->addr)
		return (free(game->img->img_ptr), NULL);
	return (game->img);
}

t_game	*ft_init_game(/* t_map *map */)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL); // error handler
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), NULL); // error handler
	game->window = mlx_new_window(game->mlx, WIDHT, HEIGHT, "cub3d");
	if (!game->window)
		return (free(game), free(game->mlx), NULL); // error handler
	//game->map = map;
	game->img = (t_image *)malloc(sizeof(t_image));
	if (!game->img)
		return (free(game), free(game->mlx), free(game->window), NULL);
	//need to double check this
	//game->img = ft_init_image(game);
	//if (!game->img)
	//	return (free(game), free(game->mlx), free(game->window), NULL);
	return (game);
}