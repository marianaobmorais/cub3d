/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_movements_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:59:24 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 17:15:56 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Activates nearby sprites based on the player's tile position.
 *
 * Iterates through all map sprites and checks if the player is on the same
 * tile or in one of the adjacent tiles (orthogonal and diagonal).
 * If so, the corresponding sprite's `sprite_action` flag is set to true.
 * This is typically used to trigger proximity-based behavior like animation,
 * interaction, or AI response from nearby sprites (e.g. enemies or NPCs).
 *
 * @param cub Pointer to the main game structure containing the player and map
 *        data.
 */
static void	ft_check_sprite_action(t_cub *cub)
{
	int			i;
	t_ipoint	tile;
	t_sprite	*sprite;

	i = 0;
	tile = cub->raycast->player_tile;
	sprite = cub->map->sprite;
	while (i < cub->map->sprite_count)
	{
		if ((tile.x == sprite[i].tile.x && tile.y == sprite[i].tile.y) \
		|| (tile.x + 1 == sprite[i].tile.x && tile.y + 1 == sprite[i].tile.y) \
		|| (tile.x - 1 == sprite[i].tile.x && tile.y - 1 == sprite[i].tile.y) \
		|| (tile.x + 1 == sprite[i].tile.x && tile.y == sprite[i].tile.y) \
		|| (tile.x == sprite[i].tile.x && tile.y + 1 == sprite[i].tile.y) \
		|| (tile.x - 1 == sprite[i].tile.x && tile.y == sprite[i].tile.y) \
		|| (tile.x == sprite[i].tile.x && tile.y - 1 == sprite[i].tile.y))
			sprite[i].sprite_action = true;
		i++;
	}
}

/**
 * @brief Updates temporary player position based on key input.
 *
 * Moves the player’s position in the temporary `tmp` coordinates according
 * to movement keys (WASD or arrow key equivalents).
 * Does not update the actual position; that is done separately via validation.
 *
 * @param keysym Key code representing the pressed movement key.
 * @param cub Pointer to the main game structure.
 * @param tmp Pointer to a temporary position used for movement calculation.
 */
void	ft_player_moves(int keysym, t_cub *cub, t_dpoint *tmp)
{
	if ((keysym == XK_A || keysym == XK_a))
		ft_move_left(cub, &(*tmp).x, &(*tmp).y);
	if ((keysym == XK_D || keysym == XK_d))
		ft_move_right(cub, &(*tmp).x, &(*tmp).y);
	if ((keysym == XK_W || keysym == XK_w))
		ft_move_up(cub, &(*tmp).x, &(*tmp).y);
	if ((keysym == XK_S || keysym == XK_s))
		ft_move_down(cub, &(*tmp).x, &(*tmp).y);
}

/**
 * @brief Handles all player-related inputs including movement, rotation, 
 * interaction, and toggling mouse input.
 *
 * Processes key inputs for rotating the view, moving the player, performing
 * actions like dropping breadcrumbs or interacting with doors, and toggling
 * mouse movement. Movement is first calculated with a temporary position,
 * and if valid, applied to the player's actual position.
 *
 * @param keysym Key code of the current input event.
 * @param cub Pointer to the main game structure.
 */
void	ft_manage_movements(int keysym, t_cub *cub)
{
	t_dpoint	tmp;

	if (keysym == XK_Left)
		ft_rotate(cub, cub->raycast->rotate_speed);
	if (keysym == XK_Right)
		ft_rotate(cub, -cub->raycast->rotate_speed);
	tmp = cub->raycast->player_pos;
	ft_player_moves(keysym, cub, &tmp);
	if ((keysym == XK_Control_R || keysym == XK_Control_L)
		&& cub->amount_action < BREAD_3 + 1)
	{
		cub->action = true;
		cub->amount_action++;
		ft_check_sprite_action(cub);
	}
	if (keysym == XK_space)
		ft_open_or_close_door(cub);
	ft_update_position(cub, tmp.x, tmp.y);
	if (keysym == XK_M || keysym == XK_m)
	{
		if (!cub->raycast->mouse_status)
			cub->raycast->mouse_status = true;
		else
			cub->raycast->mouse_status = false;
	}
}
