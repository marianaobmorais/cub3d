#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*game;

	if (argc != 2)
		ft_handle_error(strerror(EINVAL), NULL);
	game = ft_init_game(/* t_map *map */);
	if (!game)
		ft_handle_error("Malloc: t_cub", game);
	ft_loadmap(argv[1], game);
	printf("game is open\n"); //debug
	//render
	mlx_hook(game->window, KeyPress, KeyPressMask, ft_key_input, game);
	mlx_hook(game->window, DestroyNotify, NoEventMask, ft_close_window, game);
	mlx_loop(game->mlx);
	ft_print_map(game->map);
	ft_clean_cub(game);
	return (0);
}
