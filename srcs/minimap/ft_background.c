#include "../../includes/cub3d.h"

void	ft_put_minimap(t_cub *cub)
{
	if (cub->minimap->img_ptr)
		mlx_destroy_image(cub->mlx, cub->minimap->img_ptr);
	cub->minimap->img_ptr = mlx_new_image(cub->mlx, MINI_WIDTH, MINI_HEIGHT);
	if (!cub->minimap->img_ptr)
		ft_handle_error("malloc: img->img_ptr", cub);
	cub->minimap->bpp = 0;
	cub->minimap->line_len = 0;
	cub->minimap->endian = 0;
	cub->minimap->addr = mlx_get_data_addr(cub->minimap->img_ptr, \
		&cub->minimap->bpp, &cub->minimap->line_len, &cub->minimap->endian);
	if (!cub->minimap->addr)
		ft_handle_error("malloc: img->addr", cub);
	ft_render_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->minimap->img_ptr, 10, 10);
}
