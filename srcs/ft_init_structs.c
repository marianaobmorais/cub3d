
#include "../includes/cub3d.h"

void	ft_init_image(t_cub *cub)
{
	cub->image = (t_image *)malloc(sizeof(t_image));
	if (!cub->image)
		ft_handle_error("malloc: cub->image", cub);
	cub->image->img_ptr = NULL;
		if (cub->image->img_ptr)
		mlx_destroy_image(cub->mlx, cub->image->img_ptr);
	cub->image->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image->img_ptr)
		ft_handle_error("malloc: cub->image->img_ptr", cub);
	cub->image->bpp = 0;
	cub->image->line_len = 0;
	cub->image->endian = 0;
	cub->image->addr = mlx_get_data_addr(cub->image->img_ptr, &cub->image->bpp, &cub->image->line_len, &cub->image->endian);
	if (!cub->image->addr)
		ft_handle_error("malloc: cub->image->addr", cub);
}

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
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_handle_error("malloc: cub->mlx", cub);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		ft_handle_error("malloc: cub->window", cub);
	ft_init_image(cub);
	ft_init_raycast(cub);
	return (cub);
}
