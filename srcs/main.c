#include "../includes/cub3d.h"

/* DEBUG */
void	ft_print_player_info(t_map *map)
{
	printf("\nplayer position: (%d, %d)\n", map->player_pos_x, map->player_pos_y);
	printf("direction: %s\n\n",
			(map->direction == NORTH) ? "N" :
			(map->direction == SOUTH) ? "S" :
			(map->direction == WEST) ? "W" : "E");

}

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
	ft_print_player_info(cub->map); //debug
	// printf("rgb[%d, %d, %d] to hex -> %#x\n", cub->map->ceiling_rgb[0], cub->map->ceiling_rgb[1], cub->map->ceiling_rgb[2],
	// 	ft_arraytohex(cub->map->ceiling_rgb)); //debug
	mlx_hook(cub->window, KeyPress, KeyPressMask, ft_key_input, cub);
	mlx_hook(cub->window, DestroyNotify, NoEventMask, ft_close_window, cub);
	mlx_loop(cub->mlx);
	ft_clean_game(cub);
	return (0);
}
