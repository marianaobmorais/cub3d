/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_hud_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:59:03 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/02 11:17:15 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Cleans up and destroys all HUD-related images to free resources.
 *
 * This function destroys all the images related to the HUD, such as the 
 * watch, viewmodels, bread, and breadcrumbs, by calling `mlx_destroy_image`. 
 * It ensures that all image resources are properly freed when the HUD is no 
 * longer needed, preventing memory leaks.
 *
 * @param cub The main game structure containing the HUD and image data.
 */
void	ft_clean_hud(t_cub *cub)
{
	if (cub->hud->watch.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->watch.img_ptr);
	if (cub->hud->viewmodel_0.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_0.img_ptr);
	if (cub->hud->viewmodel_1.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_1.img_ptr);
	if (cub->hud->viewmodel_2.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_2.img_ptr);
	if (cub->hud->viewmodel_3.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_3.img_ptr);
	if (cub->hud->viewmodel_4.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_4.img_ptr);
	if (cub->hud->bread.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->bread.img_ptr);
	if (cub->hud->empty_bread.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->empty_bread.img_ptr);
	if (cub->hud->breadcrumbs.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->breadcrumbs.img_ptr);
	free(cub->hud);
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
	ft_init_xpm_image(cub, &cub->hud->bread, "assets/hud/bread.xpm");
	ft_init_xpm_image(cub, &cub->hud->empty_bread, "assets/hud/emptybread.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_0, "assets/hud/vwmodel_0.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_1, "assets/hud/vwmodel_1.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_2, "assets/hud/vwmodel_2.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_3, "assets/hud/vwmodel_3.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_4, "assets/hud/vwmodel_4.xpm");
	ft_init_xpm_image(cub, &cub->hud->breadcrumbs, "assets/hud/crumbs.xpm");
}
