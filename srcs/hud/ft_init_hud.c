#include "../../includes/cub3d.h"

/**
 * @brief Initializes the breads image in the HUD.
 *
 * This function allocates memory for the breads image and loads its 
 * texture from an XPM file. It also initializes image properties, 
 * handling errors if allocation fails.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_init_breads(t_cub *cub)
{
	cub->hud->breads = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->breads)
		ft_handle_error("malloc: cub->hud->breads", cub);
	ft_memset(cub->hud->breads, 0, sizeof(t_image));
	cub->hud->breads->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/hud/breads.xpm", &cub->hud->breads->width, \
		&cub->hud->breads->height);
	cub->hud->breads->addr = mlx_get_data_addr(cub->hud->breads->img_ptr, \
		&cub->hud->breads->bpp, &cub->hud->breads->line_len, \
		&cub->hud->breads->endian);
	if (!cub->hud->breads->img_ptr)
		ft_handle_error("cub->hud->breads->img_ptr", cub);
	if (!cub->hud->breads->addr)
		ft_handle_error("cub->hud->breads->addr", cub);
}

/**
 * @brief Initializes the viewmodel image in the HUD.
 *
 * This function allocates memory for the viewmodel image and loads 
 * its texture from an XPM file. It also initializes image properties, 
 * handling errors if allocation fails.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_init_viewmodel(t_cub *cub)
{
	cub->hud->viewmodel = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->viewmodel)
		ft_handle_error("malloc: cub->hud->viewmodel", cub);
	ft_memset(cub->hud->viewmodel, 0, sizeof(t_image));
	cub->hud->viewmodel->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/hud/viewmodel.xpm", &cub->hud->viewmodel->width, \
		&cub->hud->viewmodel->height);
	cub->hud->viewmodel->addr = mlx_get_data_addr(cub->hud->viewmodel->img_ptr, \
		&cub->hud->viewmodel->bpp, &cub->hud->viewmodel->line_len, \
		&cub->hud->viewmodel->endian);
	if (!cub->hud->viewmodel->img_ptr)
		ft_handle_error("cub->hud->viewmodel->img_ptr", cub);
	if (!cub->hud->viewmodel->addr)
		ft_handle_error("cub->hud->viewmodel->addr", cub);
}

/**
 * @brief Initializes the breadcrumbs image in the HUD.
 *
 * This function allocates memory for the breadcrumbs image and 
 * loads its texture from an XPM file. It also initializes image 
 * properties, handling errors if allocation fails.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_init_breadcrumbs(t_cub *cub)
{
	cub->hud->breadcrumbs = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->breadcrumbs)
		ft_handle_error("malloc: cub->hud->breadcrumbs", cub);
	ft_memset(cub->hud->breadcrumbs, 0, sizeof(t_image));
	cub->hud->breadcrumbs->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/hud/breadcrumbs.xpm", &cub->hud->breadcrumbs->width, \
		&cub->hud->breadcrumbs->height);
	cub->hud->breadcrumbs->addr = mlx_get_data_addr(\
		cub->hud->breadcrumbs->img_ptr, \
		&cub->hud->breadcrumbs->bpp, &cub->hud->breadcrumbs->line_len, \
		&cub->hud->breadcrumbs->endian);
		if (!cub->hud->breadcrumbs->img_ptr)
		ft_handle_error("cub->hud->breadcrumbs->img_ptr", cub);
	if (!cub->hud->breadcrumbs->addr)
		ft_handle_error("cub->hud->breadcrumbs->addr", cub);
}

/**
 * @brief Initializes the watch image in the HUD.
 *
 * This function allocates memory for the watch image and loads its 
 * texture from an XPM file. It also initializes image properties, 
 * handling errors if allocation fails.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_init_watch(t_cub *cub)
{
	cub->hud->watch = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->watch)
		ft_handle_error("malloc: cub->hud->watch", cub);
	ft_memset(cub->hud->watch, 0, sizeof(t_image));
	cub->hud->watch->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/hud/casio.xpm", &cub->hud->watch->width, \
		&cub->hud->watch->height);
	cub->hud->watch->addr = mlx_get_data_addr(cub->hud->watch->img_ptr, \
		&cub->hud->watch->bpp, &cub->hud->watch->line_len, \
		&cub->hud->watch->endian);
	if (!cub->hud->watch->img_ptr)
		ft_handle_error("cub->hud->watch->img_ptr", cub);
	if (!cub->hud->watch->addr)
		ft_handle_error("cub->hud->watch->addr", cub);
}

/**
 * @brief Initializes the door image in the HUD.
 *
 * This function allocates memory for the door image and loads its 
 * texture from an XPM file. It also initializes image properties, 
 * handling errors if allocation fails.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_init_door(t_cub *cub)
{
	cub->hud->door = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->door)
		ft_handle_error("malloc: cub->hud->door", cub);
	ft_memset(cub->hud->door, 0, sizeof(t_image));
	cub->hud->door->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/textures/door.xpm", &cub->hud->door->width, \
		&cub->hud->door->height); //check
	cub->hud->door->addr = mlx_get_data_addr(cub->hud->door->img_ptr, \
		&cub->hud->door->bpp, &cub->hud->door->line_len, \
		&cub->hud->door->endian);
	if (!cub->hud->door->img_ptr)
		ft_handle_error("cub->hud->door->img_ptr", cub);
	if (!cub->hud->door->addr)
		ft_handle_error("cub->hud->door->addr", cub);
}

/**
 * @brief Initializes the HUD (Heads-Up Display) for the game.
 *
 * This function allocates memory for the HUD structure and its image,
 * handling errors if allocation fails. It also initializes various 
 * HUD components, such as watch, viewmodel, breads, breadcrumbs, 
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
	cub->hud->img = (t_image *)malloc(sizeof(t_image));
	if (!cub->hud->img)
		ft_handle_error("malloc: cub->hud->img", cub);
	ft_memset(cub->hud->img, 0, sizeof(t_image));
	cub->hud->img->img_ptr = NULL;
	cub->hud->ray_hits = malloc(sizeof(t_dpoint) * WIDTH);
	ft_init_watch(cub);
	ft_init_viewmodel(cub);
	ft_init_breads(cub);
	ft_init_breadcrumbs(cub);
	ft_init_door(cub);
}
