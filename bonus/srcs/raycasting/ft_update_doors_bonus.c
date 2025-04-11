/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_doors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:06:41 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/10 21:17:58 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Toggles a door's open/close state in front of the player.
 *
 * Checks the tile directly in front of the player's current position. If a
 * door ('D') is found and its index is valid, it toggles its state:
 * - If closed, starts the opening process.
 * - If open, starts the closing process.
 * Does nothing if the tile is out of bounds or no door is found.
 *
 * @param cub A pointer to the main game structure.
 */
void	ft_open_or_close_door(t_cub *cub)
{
	t_ipoint	tl;
	int			index;

	tl.x = cub->raycast->player_tile.x + (int)round(cub->raycast->player_dir.x);
	tl.y = cub->raycast->player_tile.y + (int)round(cub->raycast->player_dir.y);
	if (tl.x < 0 || tl.x >= cub->map->height
		|| tl.y < 0 || tl.y >= cub->map->width)
		return ;
	if (cub->map->matrix[tl.x][tl.y] == 'D')
	{
		index = ft_find_door_index(cub, tl.x, tl.y);
		if (index < 0)
			return ;
		if (cub->map->door[index].status == CLOSED)
		{
			cub->map->door[index].status = OPENING;
			cub->map->door[index].move = 0;
			cub->map->door[index].timer = 0;
		}
		else if (cub->map->door[index].status == OPEN)
		{
			cub->map->door[index].status = CLOSING;
			cub->map->door[index].timer = 0;
		}
	}
}

/**
 * @brief Updates the animation state of a door while it is closing.
 *
 * Decreases the door's movement progress and updates its sprite accordingly.
 * When the movement reaches zero, the door is marked as closed and its sprite
 * is set to the fully closed image. Otherwise, it uses a frame based on the
 * current movement value to animate the door closing.
 *
 * @param cub The main game structure containing the raycast image references.
 * @param door Pointer to the door being updated.
 */
static void	closing_door(t_cub *cub, t_door *door)
{
	int	index;

	door->move -= 2;
	if (door->move <= 0)
	{
		door->move = 0;
		door->status = CLOSED;
		door->current = cub->raycast->door_closed;
	}
	else
	{
		index = door->move * (NUM_FRAMES - 1) / MAX_MOVE;
		door->current = cub->raycast->doors[index];
	}
}

/**
 * @brief Updates the animation state of a door while it is opening.
 *
 * Increments the door's movement progress and updates its sprite accordingly.
 * When the movement reaches the maximum value, the door is marked as open,
 * its timer is reset, and the sprite is set to the fully open image.
 * Otherwise, it uses a frame based on the current movement value to animate
 * the door opening.
 *
 * @param cub The main game structure containing the raycast image references.
 * @param door Pointer to the door being updated.
 */
static void	opening_door(t_cub *cub, t_door *door)
{
	int	index;

	door->move += 2;
	if (door->move >= MAX_MOVE)
	{
		door->move = MAX_MOVE;
		door->status = OPEN;
		door->timer = 0;
		door->current = cub->raycast->door_open;
	}
	else
	{
		index = door->move * (NUM_FRAMES - 1) / MAX_MOVE;
		door->current = cub->raycast->doors[index];
	}
}

/**
 * @brief Updates all doors in the map based on their current status.
 *
 * Iterates through all doors and updates their state and animation frame
 * accordingly. If a door is opening or closing, the corresponding animation
 * function is called. If a door is open, a timer tracks how long it remains
 * open, and it starts closing after a delay if the player is not on the tile.
 *
 * @param cub The main game structure containing the map and raycasting data.
 */
void	ft_update_doors(t_cub *cub)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < cub->map->door_count)
	{
		door = &cub->map->door[i];
		if (door->status == OPENING)
			opening_door(cub, door);
		else if (door->status == CLOSING)
			closing_door(cub, door);
		else if (door->status == OPEN)
		{
			door->timer += FRAME_DELTA;
			if (door->timer >= 2.0
				&& (door->tile.x != cub->raycast->player_tile.x
					|| door->tile.y != cub->raycast->player_tile.y))
			{
				door->status = CLOSING;
				door->timer = 0;
			}
		}
		door->timer += FRAME_DELTA;
		i++;
	}
}
