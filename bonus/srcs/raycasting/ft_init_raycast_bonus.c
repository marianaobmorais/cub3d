/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_raycast_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:27:19 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/02 18:56:05 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Initializes the player's direction and camera plane for facing North.
 * 
 * Sets the player's direction vector to face North and adjusts the camera plane
 * accordingly for correct field of view calculations.
 * 
 * @param raycast Pointer to the raycasting structure.
 */
static void	ft_init_north(t_raycast *raycast)
{
	raycast->player_dir.x = -1;
	raycast->player_dir.y = 0;
	raycast->camera_plane.x = 0;
	raycast->camera_plane.y = 0.66;
}

/**
 * @brief Initializes the player's direction and camera plane for facing South.
 * 
 * Sets the player's direction vector to face South and adjusts the camera plane
 * accordingly for correct field of view calculations.
 * 
 * @param raycast Pointer to the raycasting structure.
 */
static void	ft_init_south(t_raycast *raycast)
{
	raycast->player_dir.x = 1;
	raycast->player_dir.y = 0;
	raycast->camera_plane.x = 0;
	raycast->camera_plane.y = -0.66;
}

/**
 * @brief Initializes the player's direction and camera plane for facing East.
 * 
 * Sets the player's direction vector to face East and adjusts the camera plane 
 * accordingly for correct field of view calculations.
 * 
 * @param raycast Pointer to the raycasting structure.
 */
static void	ft_init_east(t_raycast *raycast)
{
	raycast->player_dir.x = 0;
	raycast->player_dir.y = 1;
	raycast->camera_plane.x = 0.66;
	raycast->camera_plane.y = 0;
}

/**
 * @brief Initializes the player's direction and camera plane for facing West.
 * 
 * Sets the player's direction vector to face West and adjusts the camera plane 
 * accordingly for correct field of view calculations.
 * 
 * @param raycast Pointer to the raycasting structure.
 */
static void	ft_init_west(t_raycast *raycast)
{
	raycast->player_dir.x = 0;
	raycast->player_dir.y = -1;
	raycast->camera_plane.x = -0.66;
	raycast->camera_plane.y = 0;
}

/**
 * @brief Initializes the raycasting structure and sets up player position and
 *        direction.
 * 
 * Allocates memory for the raycasting structure, sets the player's position in
 * the world, and calls the appropriate direction initialization function based 
 * on the player's starting direction from the map data. Also initializes
 * movement speed.
 * 
 * @param cub Pointer to the main game structure.
 */
void	ft_init_raycast(t_cub *cub)
{
	cub->raycast = (t_raycast *)malloc(sizeof(t_raycast));
	if (!cub->raycast)
		ft_handle_error("malloc: cub->raycast", cub);
	ft_memset(cub->raycast, 0, sizeof(t_raycast));
	cub->raycast->player_tile.x = cub->map->player_squ_x;
	cub->raycast->player_tile.y = cub->map->player_squ_y;
	cub->raycast->player_pos.x = (double)cub->map->player_squ_x + 0.5;
	cub->raycast->player_pos.y = (double)cub->map->player_squ_y + 0.5;
	if (cub->map->direction == NORTH)
		ft_init_north(cub->raycast);
	if (cub->map->direction == SOUTH)
		ft_init_south(cub->raycast);
	if (cub->map->direction == EAST)
		ft_init_east(cub->raycast);
	if (cub->map->direction == WEST)
		ft_init_west(cub->raycast);
}
