#include "../../includes/cub3d.h"

void	ft_init_breads(t_cub *cub)
{
	cub->hud->breads = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->breads)
		ft_handle_error("malloc: cub->hud->breads", cub);
	cub->hud->breads->height = 125;
	cub->hud->breads->width = 120;
	cub->hud->breads->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/textures/breads.xpm", &cub->hud->breads->width, \
		&cub->hud->breads->height);
	cub->hud->breads->bpp = 0;
	cub->hud->breads->endian = 0;
	cub->hud->breads->line_len = 0;
	cub->hud->breads->addr = mlx_get_data_addr(cub->hud->breads->img_ptr, \
		&cub->hud->breads->bpp, &cub->hud->breads->line_len, \
		&cub->hud->breads->endian);
}

void	ft_init_viewmodel(t_cub *cub)
{
	cub->hud->viewmodel = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->viewmodel)
		ft_handle_error("malloc: cub->hud->viewmodel", cub);
	cub->hud->viewmodel->height = 125;
	cub->hud->viewmodel->width = 120;
	cub->hud->viewmodel->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/textures/viewmodel.xpm", &cub->hud->viewmodel->width, \
		&cub->hud->viewmodel->height);
	cub->hud->viewmodel->bpp = 0;
	cub->hud->viewmodel->endian = 0;
	cub->hud->viewmodel->line_len = 0;
	cub->hud->viewmodel->addr = mlx_get_data_addr(cub->hud->viewmodel->img_ptr, \
		&cub->hud->viewmodel->bpp, &cub->hud->viewmodel->line_len, \
		&cub->hud->viewmodel->endian);
}

void	ft_init_watch(t_cub *cub)
{
	cub->hud->watch = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->watch)
		ft_handle_error("malloc: cub->hud->watch", cub);
	cub->hud->watch->height = 125;
	cub->hud->watch->width = 120;
	cub->hud->watch->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/textures/casio_w.xpm", &cub->hud->watch->width, \
		&cub->hud->watch->height);
	cub->hud->watch->bpp = 0;
	cub->hud->watch->endian = 0;
	cub->hud->watch->line_len = 0;
	cub->hud->watch->addr = mlx_get_data_addr(cub->hud->watch->img_ptr, \
		&cub->hud->watch->bpp, &cub->hud->watch->line_len, \
		&cub->hud->watch->endian);
}

void	ft_init_hud(t_cub *cub)
{
	cub->hud = (t_hud *) malloc(sizeof(t_hud));
	if (!cub->hud)
		ft_handle_error("malloc: cub->hud", cub);
	cub->hud->img = (t_image *)malloc(sizeof(t_image));
	if (!cub->hud->img)
		ft_handle_error("malloc: cub->hud->img", cub);
	cub->hud->img->img_ptr = NULL;
	ft_init_watch(cub);
	ft_init_viewmodel(cub);
	ft_init_breads(cub);
}
