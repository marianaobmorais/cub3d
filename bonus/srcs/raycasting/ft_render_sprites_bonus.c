/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_sprites_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:40:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/10 15:56:36 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Calculates the on-screen size and position of the sprite.
 *
 * Based on the sprite's depth (distance from camera), this function determines
 * its height and width, as well as the start and end positions for drawing
 * on the screen.
 *
 * @param sprite Pointer to the sprite whose drawing info will be updated.
 */
static void	ft_get_draw_info(t_sprite *sprite)
{
	(*sprite).relative_height = (int)HEIGHT / (*sprite).transform.y;
	(*sprite).relative_width = (*sprite).relative_height;
	(*sprite).start_h = -(*sprite).relative_height / 2 + HEIGHT / 2;
	(*sprite).end_h = (*sprite).relative_height / 2 + HEIGHT / 2;
	(*sprite).start_w = (*sprite).screen_w - (*sprite).relative_width / 2;
	(*sprite).end_w = (*sprite).screen_w + (*sprite).relative_width / 2;
}

/**
 * @brief Computes sprite position relative to the camera.
 *
 * This function transforms the sprite's world coordinates into camera space
 * using an inverse determinant and calculates its projected screen position and
 * depth. If the sprite is behind the player (i.e., not visible), the function
 * returns 0.
 *
 * @param cub Pointer to the main game structure.
 * @param sprite Pointer to the sprite being transformed.
 * @return Returns 1 if the sprite is in front of the camera, otherwise 0.
 */
static int	ft_get_sprite_info(t_cub *cub, t_sprite *sprite)
{
	double	relative_pos_x;
	double	relative_pos_y;
	double	inv_det;

	relative_pos_x = (*sprite).pos.x - cub->raycast->player_pos.x;
	relative_pos_y = (*sprite).pos.y - cub->raycast->player_pos.y;
	inv_det = 1.0 / (cub->raycast->player_dir.x * cub->raycast->camera_plane.y \
		- cub->raycast->player_dir.y * cub->raycast->camera_plane.x);
	(*sprite).transform.x = inv_det * (-cub->raycast->player_dir.y \
		* relative_pos_x + cub->raycast->player_dir.x * relative_pos_y);
	(*sprite).transform.y = inv_det * (cub->raycast->camera_plane.y \
		* relative_pos_x - cub->raycast->camera_plane.x * relative_pos_y);
	if ((*sprite).transform.y <= 0)
		return (0);
	(*sprite).screen_w = (int)((WIDTH / 2) * (1 + (*sprite).transform.x \
		/ (*sprite).transform.y));
	return (1);
}

/**
 * @brief Updates sprite animations over time by toggling their image state.
 *
 * This function swaps between idle, move, or action sprites depending on the
 * current time counter and the state of the sprite. Used to simulate animation.
 * Resets the timer if more than 0.4 seconds have passed.
 *
 * @param cub Pointer to the main game structure.
 */
static void	ft_update_sprites(t_cub *cub)
{
	int	i;

	if (cub->raycast->time >= 0.4)
	{
		i = 0;
		while (i < cub->map->sprite_count)
		{
			if (cub->map->sprite[i].status)
			{
				cub->map->sprite[i].img = cub->raycast->sprite_still;
				cub->map->sprite[i].status = false;
			}
			else if (!cub->map->sprite[i].status)
			{
				if (cub->map->sprite[i].sprite_action)
					cub->map->sprite[i].img = cub->raycast->sprite_eat;
				else
					cub->map->sprite[i].img = cub->raycast->sprite_move;
				cub->map->sprite[i].status = true;
			}
			i++;
		}
		cub->raycast->time = 0;
	}
	cub->raycast->time += 0.016;
}

/**
 * @brief Sorts the sprites in descending order of distance from the player.
 *
 * Implements a simple bubble sort to arrange sprites so that distant ones are
 * drawn first. This ensures correct rendering with overlapping transparency and
 * depth effects.
 *
 * @param map Pointer to the map structure containing sprites.
 * @param ray Pointer to the raycasting structure for player position reference.
 */
static void	ft_sort_sprites(t_map *map, t_raycast *ray)
{
	int			i;
	int			count;
	t_sprite	tmp;

	i = -1;
	while (++i < map->sprite_count)
		map->sprite[i].dist = (ray->player_pos.x - map->sprite[i].pos.x) \
		* (ray->player_pos.x - map->sprite[i].pos.x) + (ray->player_pos.y \
		- map->sprite[i].pos.y) * (ray->player_pos.y - map->sprite[i].pos.y);
	count = map->sprite_count;
	while (count)
	{
		i = -1;
		while (++i < count - 1)
		{
			if (map->sprite[i].dist < map->sprite[i + 1].dist)
			{
				tmp = map->sprite[i];
				map->sprite[i] = map->sprite[i + 1];
				map->sprite[i + 1] = tmp;
			}
		}
		count--;
	}
}

/**
 * @brief Renders all visible sprites in the scene.
 *
 * This function sorts and updates sprite animations, calculates their on-screen
 * positions and sizes, and draws them column by column while respecting depth
 * buffering to ensure correct layering with walls and other sprites.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_render_sprites(t_cub *cub)
{
	int	i;
	int	w;

	ft_sort_sprites(cub->map, cub->raycast);
	ft_update_sprites(cub);
	i = 0;
	while (i < cub->map->sprite_count)
	{
		if (ft_get_sprite_info(cub, &cub->map->sprite[i]))
		{
			ft_get_draw_info(&cub->map->sprite[i]);
			w = cub->map->sprite[i].start_w;
			while (w < cub->map->sprite[i].end_w)
			{
				if (w >= 0 && w < WIDTH && cub->map->sprite[i].transform.y \
						< cub->raycast->buffer[w])
					ft_draw_sprite(cub, cub->map->sprite[i], w);
				w++;
			}
		}
		i++;
	}
}
