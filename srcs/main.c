#include "../includes/cub3d.h"

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
	mlx_hook(cub->window, KeyPress, KeyPressMask, ft_key_input, cub);
	mlx_hook(cub->window, DestroyNotify, NoEventMask, ft_close_window, cub);
	mlx_loop(cub->mlx);
	ft_print_map(cub->map); //debug
	ft_clean_cub(cub);
	return (0);
}
