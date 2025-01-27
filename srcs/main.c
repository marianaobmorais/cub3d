#include "../includes/cub3d.h"


int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = (t_cub *) malloc(sizeof(t_cub));
	if (!cub)
		ft_handle_error("Malloc: t_cub", cub);
	if (argc != 2)
		ft_handle_error(strerror(EINVAL), cub);
	ft_loadmap(argv[1], cub);
	printf("Starting cub3D...\n");
	ft_print_map(cub->map);
	ft_clean_cub(cub);
	return (0);
}
