/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_hud_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:59:03 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/09 20:11:42 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_init_xpm_image(cub, &cub->hud->bread, "assets/hud/bread.xpm");
	ft_init_xpm_image(cub, &cub->hud->empty_bread, "assets/hud/emptybread.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_0, "assets/hud/vwmodel_0.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_1, "assets/hud/vwmodel_1.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_2, "assets/hud/vwmodel_2.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_3, "assets/hud/vwmodel_3.xpm");
	ft_init_xpm_image(cub, &cub->hud->viewmodel_4, "assets/hud/vwmodel_4.xpm");
	ft_init_xpm_image(cub, &cub->hud->breadcrumbs, "assets/hud/crumbs.xpm");
}
