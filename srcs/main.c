#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = NULL;
	if (argc != 2)
		ft_handle_error(strerror(EINVAL), cub);
	//ft_memset(cub, 0, sizeof(cub)); //not sure if it's needed
	cub = ft_init_structs(cub);
	ft_load_map(argv[1], cub);
	ft_print_map(cub->map); //debug
	ft_run_game(cub);
	mlx_loop_hook(cub->mlx, ft_put_start_screen, cub);
	mlx_hook(cub->window, KeyPress, KeyPressMask, ft_key_input, cub);
	mlx_hook(cub->window, DestroyNotify, NoEventMask, ft_close_window, cub);
	mlx_loop(cub->mlx);
	ft_clean_game(cub);
	return (0);
}
