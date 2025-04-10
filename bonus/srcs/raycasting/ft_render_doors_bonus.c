/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_doors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:06:29 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/10 22:02:01 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Initializes door textures and sets default door states.
 *
 * Loads all door-related textures from .xpm files into the raycast struct,
 * including the closed door, open door, door animation frames, and the
 * grab-go image. Sets all doors on the map to the closed state initially.
 *
 * @param cub A pointer to the main game structure.
 */
void	ft_init_doors(t_cub *cub)
{
	int	i;

	i = 0;
	ft_init_xpm_image(cub, &cub->raycast->door_closed, "assets/door/door.xpm");
	ft_init_xpm_image(cub, &cub->raycast->door_open, "assets/door/door13.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[0], "assets/door/door1.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[1], "assets/door/door2.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[2], "assets/door/door3.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[3], "assets/door/door4.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[4], "assets/door/door5.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[5], "assets/door/door6.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[6], "assets/door/door7.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[7], "assets/door/door8.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[8], "assets/door/door9.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[9], "assets/door/door10.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[10], "assets/door/door11.xpm");
	ft_init_xpm_image(cub, &cub->raycast->doors[11], "assets/door/door12.xpm");
	ft_init_xpm_image(cub, &cub->raycast->grab_go, "assets/textures/grab_go.xpm");
	ft_init_xpm_image(cub, &cub->raycast->grab_go2, "assets/textures/grab_go2.xpm");
	while (i < cub->map->door_count)
	{
		(cub->map->door)[i].current = cub->raycast->door_closed;
		i++;
	}
}

/**
 * @brief Finds the index of a door in the map's door array by tile coords.
 *
 * Iterates through the door array to locate a door at the specified
 * tile position (x, y). Returns the index if found, or -1 if not found.
 *
 * @param cub A pointer to the main game structure.
 * @param x The x-coordinate of the door tile.
 * @param y The y-coordinate of the door tile.
 * @return The index of the door if found, otherwise -1.
 */
int	ft_find_door_index(t_cub *cub, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub->map->door_count)
	{
		if (x == (cub->map->door)[i].tile.x
			&& y == (cub->map->door)[i].tile.y)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Paints an internal wall segment if adjacent to a door tile.
 *
 * Checks whether the wall hit by the ray is adjacent to a door tile
 * ('D') in the map matrix. If so, it draws the corresponding internal
 * wall using a predefined texture.
 *
 * @param cub A pointer to the main game structure.
 * @param w The screen column being processed.
 */
void	ft_paint_internal_wall(t_cub *cub, int w)
{
	t_ipoint	tile;
	char		**matrix;

	tile = cub->raycast->step_tile;
	matrix = cub->map->matrix;
	if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x < 0
		&& tile.x + 1 < cub->map->height && matrix[tile.x + 1][tile.y] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go2);
	else if (cub->raycast->hit_side == 0 && cub->raycast->ray_dir.x >= 0
		&& tile.x > 0 && matrix[tile.x - 1][tile.y] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go);
	else if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y < 0
		&& tile.y + 1 < cub->map->width && matrix[tile.x][tile.y + 1] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go);
	else if (cub->raycast->hit_side == 1 && cub->raycast->ray_dir.y >= 0
		&& tile.y > 0 && matrix[tile.x][tile.y - 1] == 'D')
		ft_paint_ray(cub, w, cub->raycast->grab_go2);
}

/**
 * @brief Renders all doors detected by the current raycast.
 *
 * Iterates through all doors hit during the raycast process, calculates the
 * exact wall hit position for texture mapping, and draws each door slice
 * using its corresponding texture and position.
 *
 * @param cub A pointer to the main game structure.
 * @param w The current screen column being rendered.
 */
void	ft_render_doors(t_cub *cub, int w)
{
	int		index;
	t_door	*door;

	while (cub->raycast->door_increment > -1)
	{
		index = ft_find_door_index(cub, \
			cub->raycast->doors_found[cub->raycast->door_increment].x, \
			cub->raycast->doors_found[cub->raycast->door_increment].y);
		door = &cub->map->door[index];
		if (door->door_side == 0)
			door->wall_hit = cub->raycast->player_pos.y + door->door_dist * \
			cub->raycast->ray_dir.y;
		else
			door->wall_hit = cub->raycast->player_pos.x + door->door_dist * \
			cub->raycast->ray_dir.x;
		door->wall_hit -= floor(door->wall_hit);
		ft_paint_ray_door(cub, w, *door);
		cub->raycast->door_increment--;
	}
	cub->raycast->hit_door = false;
	cub->raycast->door_increment = -1;
}
