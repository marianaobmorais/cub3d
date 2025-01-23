# include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game	*game;

	//argv check
	//map check

	// char *map[8] =
	// {
	// 	"111111111111",
	// 	"100000000001",
	// 	"100000001001",
	// 	"100000000001",
	// 	"100110000001",
	// 	"100111000001",
	// 	"100000000001",
	// 	"111111111111"
	// }; //temp

	game = ft_init_game(/* t_map *map */);
	if (!game)
		return (1); //error handler
	printf("game is open\n"); //debug
	//render
	mlx_hook(game->window, KeyPress, KeyPressMask, ft_key_input, game);
	mlx_hook(game->window, DestroyNotify, NoEventMask, ft_close_window, game);
	mlx_loop(game->mlx);
	return (0);
}