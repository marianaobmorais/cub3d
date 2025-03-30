#include "../../includes/cub3d_bonus.h"

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
}
