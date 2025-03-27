#include "../../includes/cub3d_bonus.h"

/**
 * @brief Initializes the empty_bread image in the HUD.
 *
 * This function allocates memory for the empty_bread image and loads its 
 * texture from an XPM file. It also initializes image properties, 
 * handling errors if allocation fails.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_init_bread(t_cub *cub)
{
	cub->hud->bread = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->bread)
		ft_handle_error("malloc: cub->hud->bread", cub);
	ft_memset(cub->hud->bread, 0, sizeof(t_image));
	cub->hud->bread->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/hud/bread.xpm", &cub->hud->bread->width, \
		&cub->hud->bread->height);
	cub->hud->bread->addr = mlx_get_data_addr(cub->hud->bread->img_ptr, \
		&cub->hud->bread->bpp, &cub->hud->bread->line_len, \
		&cub->hud->bread->endian);
	if (!cub->hud->bread->img_ptr)
		ft_handle_error("cub->hud->bread->img_ptr", cub);
	if (!cub->hud->bread->addr)
		ft_handle_error("cub->hud->bread->addr", cub);
}

void	ft_init_empty_bread(t_cub *cub)
{
	cub->hud->empty_bread = (t_image *) malloc(sizeof(t_image));
	if (!cub->hud->empty_bread)
		ft_handle_error("malloc: cub->hud->empty_bread", cub);
	ft_memset(cub->hud->empty_bread, 0, sizeof(t_image));
	cub->hud->empty_bread->img_ptr = mlx_xpm_file_to_image(cub->mlx, \
		"assets/hud/empty_bread.xpm", &cub->hud->empty_bread->width, \
		&cub->hud->empty_bread->height);
	cub->hud->empty_bread->addr = mlx_get_data_addr(cub->hud->empty_bread->img_ptr, \
		&cub->hud->empty_bread->bpp, &cub->hud->empty_bread->line_len, \
		&cub->hud->empty_bread->endian);
	if (!cub->hud->empty_bread->img_ptr)
		ft_handle_error("cub->hud->empty_bread->img_ptr", cub);
	if (!cub->hud->empty_bread->addr)
		ft_handle_error("cub->hud->empty_bread->addr", cub);
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
	cub->hud->img = (t_image *)malloc(sizeof(t_image));
	if (!cub->hud->img)
		ft_handle_error("malloc: cub->hud->img", cub);
	ft_memset(cub->hud->img, 0, sizeof(t_image));
	cub->hud->img->img_ptr = NULL;
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
