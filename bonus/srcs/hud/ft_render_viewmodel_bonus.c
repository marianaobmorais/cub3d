/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_viewmodel_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:00:03 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/01 23:00:04 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Selects and returns the appropriate viewmodel image based on the 
 *        player's action state.
 *
 * This function determines which viewmodel image to use based on the player's 
 * amount of actions. The image is selected from a set of viewmodel images, 
 * cycling through them based on the action count. If the action count exceeds 
 * a specific threshold, `NULL` is returned.
 *
 * @param cub The main game struct containing the player's state and HUD data.
 *
 * @return A pointer to the selected viewmodel image, or `NULL` if no image 
 *         is selected.
 */
static t_image	*ft_setting_viewmodel(t_cub *cub)
{
	int	step;
	int	vm;

	if (cub->amount_action > BREAD_3)
		return (NULL);
	step = (cub->amount_action - 1) / 2;
	vm = (step % 4) + 1;
	if (vm == 1)
		return (&cub->hud->viewmodel_1);
	if (vm == 2)
		return (&cub->hud->viewmodel_2);
	if (vm == 3)
		return (&cub->hud->viewmodel_3);
	if (vm == 4)
		return (&cub->hud->viewmodel_4);
	return (NULL);
}

/**
 * @brief Renders the viewmodel and HUD elements based on the player's state.
 *
 * This function displays the viewmodel at the center of the screen and 
 * updates the HUD elements based on the player's current action. The 
 * viewmodel and bread icons are rendered dynamically based on the amount 
 * of actions the player has performed.
 *
 * @param cub The main game struct containing the player's state and HUD data.
 */
void	ft_render_viewmodel(t_cub *cub)
{
	int	pos_x;
	int	pos_y;

	pos_x = (WIDTH - 256) / 2;
	pos_y = HEIGHT - 256;
	if (cub->amount_action <= BREAD_3)
		ft_render_source_on_hud(cub, ft_setting_viewmodel(cub), pos_x, pos_y);
	else
		ft_render_source_on_hud(cub, &cub->hud->viewmodel_0, pos_x, pos_y);
	if (cub->amount_action > BREAD_1)
		ft_render_source_on_hud(cub, &cub->hud->empty_bread, WIDTH - 128, 0);
	else
		ft_render_source_on_hud(cub, &cub->hud->bread, WIDTH - 128, 0);
	if (cub->amount_action > BREAD_2)
		ft_render_source_on_hud(cub, &cub->hud->empty_bread, WIDTH - 192, 0);
	else
		ft_render_source_on_hud(cub, &cub->hud->bread, WIDTH - 192, 0);
	if (cub->amount_action > BREAD_3)
		ft_render_source_on_hud(cub, &cub->hud->empty_bread, WIDTH - 256, 0);
	else
		ft_render_source_on_hud(cub, &cub->hud->bread, WIDTH - 256, 0);
}
