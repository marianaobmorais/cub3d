
#include "../includes/cub3d.h"

t_cub	*ft_init_structs(t_cub *cub, char *argv)
{
	cub = (t_cub *) malloc(sizeof(t_cub));
	if (!cub)
		ft_handle_error("malloc: cub", cub);
	ft_load_map(argv, cub);
	cub->mlx = NULL;
	cub->window = NULL;
	cub->image = NULL;
	//cub->minimap = NULL;
	cub->raycast = NULL;
	ft_init_raycast(cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_handle_error("malloc: cub->mlx", cub);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		ft_handle_error("malloc: cub->window", cub);
	cub->image = (t_image *)malloc(sizeof(t_image));
	if (!cub->image)
		ft_handle_error("malloc: cub->image", cub);
	cub->image->img_ptr = NULL;
	return (cub);
}
