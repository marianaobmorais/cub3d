/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_parser_utils_2_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:34 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/09 19:37:49 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

bool	is_valid_sprite(char *line, char *previous_line, int x)
{
  //add brief
	(void)previous_line;
	if (previous_line)
	{
		if (previous_line[x] && previous_line[x] == ' ')
			return (false);
	}
	if (x > 0 && line[x - 1] != ' ' && line[x + 1] != ' '
		&& line[x + 1] != '\0')
		return (true);
	return (false);
}

/**
 * @brief Sets a sprite at the given (x, y) position in the map.
 *
 * This function assigns the position of a sprite in the map structure, 
 * updating its coordinates and assigning it a unique ID based on the 
 * current sprite increment counter.
 *
 * @param cub The main game structure containing the map data.
 * @param x The x-coordinate of the sprite in the map.
 * @param y The y-coordinate of the sprite in the map.
 */
void	ft_set_sprite(t_cub *cub, int x, int y)
{
	(cub->map->sprite[cub->map->sprite_increment]).tile.x = y;
	(cub->map->sprite[cub->map->sprite_increment]).tile.y = x;
	(cub->map->sprite[cub->map->sprite_increment]).id = \
	cub->map->sprite_increment;
	cub->map->sprite_increment++;
}

/**
 * @brief Counts the number of sprites in a given map line.
 *
 * This function iterates through the provided line and increments the 
 * sprite count in the map structure for each occurrence of the sprite 
 * character ('X').
 *
 * @param cub The main game structure containing the map data.
 * @param line The current line of the map being analyzed.
 */
void	ft_count_sprites(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'X')
			cub->map->sprite_count++;
		i++;
	}
}

/**
 * @brief Sets a door at the given (x, y) position in the map.
 *
 * This function assigns the position of a door in the map structure, 
 * updating its coordinates and assigning it a unique ID based on the 
 * current door increment counter.
 *
 * @param cub The main game structure containing the map data.
 * @param x The x-coordinate of the door in the map.
 * @param y The y-coordinate of the door in the map.
 */
void	ft_set_door(t_cub *cub, int x, int y)
{
	ft_memset(&cub->map->door[cub->map->door_increment], 0, sizeof(t_door));
	(cub->map->door[cub->map->door_increment]).tile.x = y;
	(cub->map->door[cub->map->door_increment]).tile.y = x;
	(cub->map->door[cub->map->door_increment]).id = cub->map->door_increment;
	//(cub->map->door[cub->map->door_increment]).timer = 0;
	(cub->map->door[cub->map->door_increment]).move = -1;
	(cub->map->door[cub->map->door_increment]).status = OPEN;
	cub->map->door_increment++;
}

/**
 * @brief Counts the number of doors in a given map line.
 *
 * This function iterates through the provided line and increments the 
 * door count in the map structure for each occurrence of the door 
 * character ('X').
 *
 * @param cub The main game structure containing the map data.
 * @param line The current line of the map being analyzed.
 */
void	ft_count_doors(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'D')
			cub->map->door_count++;
		i++;
	}
}
