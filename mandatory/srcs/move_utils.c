/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:38:45 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/24 14:39:25 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Moves the player to the left.
 *
 * Adjusts the temporary player position by moving left based on the camera 
 * plane direction and movement speed.
 *
 * @param cub Pointer to the main game structure.
 * @param tmp_x Pointer to the temporary x-coordinate of the player.
 * @param tmp_y Pointer to the temporary y-coordinate of the player.
 */
void	ft_move_left(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x -= cub->raycast->camera_plane.x * cub->raycast->move_speed;
	*tmp_y -= cub->raycast->camera_plane.y * cub->raycast->move_speed;
}

/**
 * @brief Moves the player to the right.
 *
 * Adjusts the temporary player position by moving right based on the camera 
 * plane direction and movement speed.
 *
 * @param cub Pointer to the main game structure.
 * @param tmp_x Pointer to the temporary x-coordinate of the player.
 * @param tmp_y Pointer to the temporary y-coordinate of the player.
 */
void	ft_move_right(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x += cub->raycast->camera_plane.x * cub->raycast->move_speed;
	*tmp_y += cub->raycast->camera_plane.y * cub->raycast->move_speed;
}

/**
 * @brief Moves the player forward.
 *
 * Adjusts the temporary player position by moving forward based on the player's
 * direction vector and movement speed.
 *
 * @param cub Pointer to the main game structure.
 * @param tmp_x Pointer to the temporary x-coordinate of the player.
 * @param tmp_y Pointer to the temporary y-coordinate of the player.
 */
void	ft_move_up(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x += cub->raycast->player_dir.x * cub->raycast->move_speed;
	*tmp_y += cub->raycast->player_dir.y * cub->raycast->move_speed;
}

/**
 * @brief Moves the player backward.
 *
 * Adjusts the temporary player position by moving backward based on the
 * player's direction vector and movement speed.
 *
 * @param cub Pointer to the main game structure.
 * @param tmp_x Pointer to the temporary x-coordinate of the player.
 * @param tmp_y Pointer to the temporary y-coordinate of the player.
 */
void	ft_move_down(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x -= cub->raycast->player_dir.x * cub->raycast->move_speed;
	*tmp_y -= cub->raycast->player_dir.y * cub->raycast->move_speed;
}

/**
 * @brief Updates the player's position.
 *
 * Sets the player's actual position and square (tile) position based on the 
 * temporary coordinates.
 *
 * @param cub Pointer to the main game structure.
 * @param tmp_x The updated x-coordinate of the player.
 * @param tmp_y The updated y-coordinate of the player.
 */
void	ft_update_position(t_cub *cub, double tmp_x, double tmp_y)
{
	cub->raycast->player_pos.x = tmp_x;
	cub->raycast->player_pos.y = tmp_y;
	cub->raycast->player_squ.x = (int)tmp_x;
	cub->raycast->player_squ.y = (int)tmp_y;
}
