# include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game	*game;

	printf("cub3D\n"); //debug
	//argv check
	//map check
	game = ft_init_game(/* t_map *map */);
	if (!game)
		return (1); //error handler
	//render
	mlx_hook(game->window, KeyPress, KeyPressMask, ft_key_input, game);
	mlx_hook(game->window, DestroyNotify, NoEventMask, ft_close_window, game);
	mlx_loop(game->mlx);
	return (0);
}