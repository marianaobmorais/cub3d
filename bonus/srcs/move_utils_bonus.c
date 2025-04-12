/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:38:45 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 15:31:55 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	//update brief
	t_raycast	*ray;
	int			index;

	ray = cub->raycast;
	if (!(tmp_x >= 0 && tmp_x < cub->map->height
		&& tmp_y >= 0 && tmp_y < cub->map->width)
		|| cub->map->matrix[(int)tmp_x][(int)tmp_y] == 32)
		return ;
	if (cub->map->matrix[(int)tmp_x][(int)tmp_y] == 'D')
	{
		index = ft_find_door_index(cub, (int)tmp_x, (int)tmp_y);
		if (index >= 0)
		{
			if (cub->map->door[index].status == CLOSED
				|| cub->map->door[index].status == CLOSING
				|| cub->map->door[index].status == OPENING)
				return ;
		}
	}
	if (cub->map->matrix[(int)tmp_x][(int)tmp_y] != '1'
		&& cub->map->matrix[(int)ray->player_pos.x][(int)tmp_y] != '1'
		&& cub->map->matrix[(int)tmp_x][(int)ray->player_pos.y] != '1')
	{
		ray->player_pos.x = tmp_x;
		ray->player_pos.y = tmp_y;
		ray->player_tile.x = (int)tmp_x;
		ray->player_tile.y = (int)tmp_y;
	}
}
