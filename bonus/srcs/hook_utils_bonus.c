/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:56:33 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 16:59:21 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Closes the game window and exits the program.
 *
 * Cleans up allocated resources, calls the game cleanup function, and 
 * terminates the program with an exit status of 0.
 *
 * @param cub Pointer to the main game structure.
 * @return Always returns 0.
 */
int	ft_close_window(t_cub *cub)
{
	ft_clean_game(cub);
	exit(0);
}

/**
 * @brief Rotates the player's direction and camera plane.
 *
 * Applies a rotation matrix to the player's direction vector and camera plane 
 * based on the given angle, allowing the player to look left or right.
 *
 * @param cub Pointer to the main game structure.
 * @param angle The rotation angle in radians (positive for left, negative for
 *        right).
 */
void	ft_rotate(t_cub *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->raycast->player_dir.x;
	cub->raycast->player_dir.x = cub->raycast->player_dir.x * cos(angle)
		- cub->raycast->player_dir.y * sin(angle);
	cub->raycast->player_dir.y = old_dir_x * sin(angle)
		+ cub->raycast->player_dir.y * cos(angle);
	old_plane_x = cub->raycast->camera_plane.x;
	cub->raycast->camera_plane.x = cub->raycast->camera_plane.x * cos(angle)
		- cub->raycast->camera_plane.y * sin(angle);
	cub->raycast->camera_plane.y = old_plane_x * sin(angle)
		+ cub->raycast->camera_plane.y * cos(angle);
}

/**
 * @brief Handles user input when the exit screen is active.
 *
 * Responds to key presses to select and confirm exit options. 
 * Arrow keys or W/S are used to toggle between options. Pressing Enter with
 * the selected option either closes the window or cancels the exit and redraws
 * the main screen.
 *
 * @param keysym The key symbol pressed by the user.
 * @param cub A pointer to the main game structure.
 */
static void	ft_manage_exit(int keysym, t_cub *cub)
{
	static int	dir;

	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
	{
		dir = 1;
		ft_put_end_screen(cub, dir);
	}
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
	{
		dir = 0;
		ft_put_end_screen(cub, dir);
	}
	if (keysym == XK_Return && dir == 1)
		ft_close_window(cub);
	if (keysym == XK_Return && dir == 0)
	{
		cub->leaving = false;
		ft_handle_img(cub);
	}
}

/**
 * @brief Handles all key inputs during game runtime and at startup.
 *
 * This function processes key events based on the current game state. It
 * starts the game on Enter, exits on Escape before starting, manages the exit
 * screen when Escape is pressed during gameplay, and routes movement or exit
 * handling accordingly.
 *
 * @param keysym The key symbol pressed by the user.
 * @param cub A pointer to the main game structure.
 * @return Always returns 0.
 */
int	ft_key_input(int keysym, t_cub *cub)
{
	if (cub->started == false && keysym == XK_Return)
	{
		cub->started = true;
		ft_handle_img(cub);
	}
	if (cub->started == false && keysym == XK_Escape)
		ft_close_window(cub);
	if (cub->started == true && keysym == XK_Escape)
	{
		if (cub->leaving == true)
		{
			cub->leaving = false;
			ft_handle_img(cub);
			return (0);
		}
		cub->leaving = true;
		ft_put_end_screen(cub, 0);
	}
	if (cub->started == true && cub->leaving == true)
		ft_manage_exit(keysym, cub);
	if (cub->started == true && cub->leaving == false)
		ft_manage_movements(keysym, cub);
	return (0);
}
