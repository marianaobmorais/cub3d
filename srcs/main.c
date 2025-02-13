#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = NULL;
	if (argc != 2)
		ft_handle_error(strerror(EINVAL), cub);
	cub = (t_cub *) malloc(sizeof(t_cub));
	if (!cub)
		ft_handle_error("malloc: cub", cub);
	//ft_memset(cub, 0, sizeof(cub)); //not sure if it's needed
	ft_loadmap(argv[1], cub);
	cub = ft_init_game(cub);
	if (!cub)
		return (1); //error handler
	ft_print_map(cub->map); //debug
	mlx_hook(cub->window, KeyPress, KeyPressMask, ft_key_input, cub);
	mlx_hook(cub->window, DestroyNotify, NoEventMask, ft_close_window, cub);
	mlx_loop(cub->mlx);
	ft_clean_game(cub);
	return (0);
}
