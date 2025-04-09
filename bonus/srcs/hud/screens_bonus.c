/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 23:13:15 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/02 17:40:39 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Initializes the game's start and end screens.
 *
 * This function loads the XPM images for the start and end screens, storing 
 * them in the `cub->screens` structure. It sets the initial screen index 
 * to zero, ensuring that the first screen is displayed at the start.
 *
 * @param cub A pointer to the main game structure containing screen data.
 */
void	ft_init_screens(t_cub *cub)
{
	cub->screens.current_screen = 0;
	ft_init_xpm_image(cub, &cub->screens.start_0, \
		"assets/screens/start_screen0.xpm");
	ft_init_xpm_image(cub, &cub->screens.start_1, \
		"assets/screens/start_screen1.xpm");
	ft_init_xpm_image(cub, &cub->screens.start_2, \
		"assets/screens/start_screen2.xpm");
	ft_init_xpm_image(cub, &cub->screens.start_3, \
		"assets/screens/start_screen3.xpm");
	ft_init_xpm_image(cub, &cub->screens.end_0, \
		"assets/screens/end_screen0.xpm");
	ft_init_xpm_image(cub, &cub->screens.end_1, \
		"assets/screens/end_screen1.xpm");
}

/**
 * @brief Frees the memory allocated for the game's start and end screens.
 *
 * This function destroys the XPM images associated with the start and end 
 * screens, ensuring that the allocated memory is properly released.
 *
 * @param cub A pointer to the main game structure containing screen data.
 */
void	ft_clean_screens(t_cub *cub)
{
	if (cub->screens.start_0.img_ptr)
		mlx_destroy_image(cub->mlx, cub->screens.start_0.img_ptr);
	if (cub->screens.start_1.img_ptr)
		mlx_destroy_image(cub->mlx, cub->screens.start_1.img_ptr);
	if (cub->screens.start_2.img_ptr)
		mlx_destroy_image(cub->mlx, cub->screens.start_2.img_ptr);
	if (cub->screens.start_3.img_ptr)
		mlx_destroy_image(cub->mlx, cub->screens.start_3.img_ptr);
	if (cub->screens.end_0.img_ptr)
		mlx_destroy_image(cub->mlx, cub->screens.end_0.img_ptr);
	if (cub->screens.end_1.img_ptr)
		mlx_destroy_image(cub->mlx, cub->screens.end_1.img_ptr);
}

/**
 * @brief Displays the appropriate end screen based on the given direction.
 *
 * This function renders one of the end screen images onto the game window 
 * depending on the value of `dir`. If `dir` is 0, it displays `end_0`; 
 * if `dir` is 1, it displays `end_1`.
 *
 * @param cub A pointer to the main game structure containing screen data.
 * @param dir The direction that determines which end screen to display.
 *
 * @return Always returns 0.
 */
int	ft_put_end_screen(t_cub *cub, int dir)
{
	if (dir == 0)
		mlx_put_image_to_window(cub->mlx, cub->window, \
			cub->screens.end_0.img_ptr, 0, 0);
	if (dir == 1)
		mlx_put_image_to_window(cub->mlx, cub->window, \
			cub->screens.end_1.img_ptr, 0, 0);
	return (0);
}

/**
 * @brief Displays the start screen animation frame by frame.
 *
 * This function cycles through the start screen images and renders them 
 * onto the game window. It ensures the `current_screen` index loops back 
 * to 0 after reaching the last frame.
 *
 * @param cub A pointer to the main game structure containing screen data.
 */
void	ft_put_start_screen(t_cub *cub)
{
	if (cub->screens.current_screen == 4)
		cub->screens.current_screen = 0;
	if (cub->screens.current_screen == 0)
		mlx_put_image_to_window(cub->mlx, cub->window, \
			cub->screens.start_0.img_ptr, 0, 0);
	if (cub->screens.current_screen == 1)
		mlx_put_image_to_window(cub->mlx, cub->window, \
			cub->screens.start_1.img_ptr, 0, 0);
	if (cub->screens.current_screen == 2)
		mlx_put_image_to_window(cub->mlx, cub->window, \
			cub->screens.start_2.img_ptr, 0, 0);
	if (cub->screens.current_screen == 3)
		mlx_put_image_to_window(cub->mlx, cub->window, \
			cub->screens.start_3.img_ptr, 0, 0);
	cub->screens.current_screen++;
}
