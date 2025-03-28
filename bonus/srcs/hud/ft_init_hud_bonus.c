#include "../../includes/cub3d_bonus.h"

void	ft_init_xpm_image(t_cub *cub, t_image **img, char *path)
{
	*img = (t_image *)malloc(sizeof(t_image));
	if (!*img)
		ft_handle_error("malloc: img", cub);
	ft_memset(*img, 0, sizeof(t_image));
	(*img)->img_ptr = mlx_xpm_file_to_image(cub->mlx, path, 
		&(*img)->width, &(*img)->height);
	if (!(*img)->img_ptr)
		ft_handle_error("mlx_xpm_file_to_image", cub);
	(*img)->addr = mlx_get_data_addr((*img)->img_ptr, &(*img)->bpp, \
		&(*img)->line_len, &(*img)->endian);
	if (!(*img)->addr)
		ft_handle_error("mlx_get_data_addr", cub);
}

/**
 * @brief Initializes the HUD (Heads-Up Display) for the game.
 *
 * This function allocates memory for the HUD structure and its image,
 * handling errors if allocation fails. It also initializes various 
 * HUD components, such as watch, viewmodel, empty_bread, breadcrumbs, 
 * and doors.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_init_hud(t_cub *cub)
{
	cub->hud = (t_hud *) malloc(sizeof(t_hud));
	if (!cub->hud)
		ft_handle_error("malloc: cub->hud", cub);
	ft_memset(cub->hud, 0, sizeof(t_hud));
	ft_init_xpm_image(cub, &cub->hud->watch, "assets/hud/casio.xpm");
	ft_init_xpm_image(cub, &cub->hud->bread, "assets/hud/bread.xpm"); //bag
	ft_init_xpm_image(cub, &cub->hud->empty_bread, "assets/hud/empty_bread.xpm"); //bag
	ft_init_xpm_image(cub, &cub->hud->viewmodel, "assets/hud/viewmodel.xpm");
	ft_init_xpm_image(cub, &cub->hud->breadcrumbs, "assets/hud/breadcrumbs.xpm");
	//ft_init_watch(cub);
	// ft_init_viewmodel(cub);
	// ft_init_bread(cub);
	// ft_init_empty_bread(cub);
	// ft_init_breadcrumbs(cub);
	// ft_init_door(cub);
}
