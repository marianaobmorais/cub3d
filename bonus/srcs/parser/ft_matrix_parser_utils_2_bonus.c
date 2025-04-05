/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_parser_utils_2_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:34 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/05 16:20:39 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Validates if a sprite at position (x) in a line is correctly placed 
 *        based on surrounding characters.
 *
 * This function checks if the sprite is properly positioned within the grid. 
 * It ensures that the sprite is not preceded by a space in the previous line 
 * and is surrounded by non-space characters on both sides in the current line.
 *
 * @param line The current line in the map.
 * @param previous_line The previous line in the map (for vertical checks).
 * @param x The current position (index) in the line.
 *
 * @return `true` if the sprite position is valid, `false` otherwise.
 */
bool	is_valid_sprite(char *line, char *previous_line, int x)
{
	(void)previous_line;
	if (previous_line)
	{
		if (previous_line[x] && previous_line[x] == ' ')
		{
			return (false);
		}
	}
	if (x > 0 && line[x - 1] != ' ' && line[x + 1] != ' '
		&& line[x + 1] != '\0')
	{
		return (true);
	}
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
	(cub->map->door[cub->map->door_increment]).timer = 0;
	(cub->map->door[cub->map->door_increment]).move = -1;
	(cub->map->door[cub->map->door_increment]).status = OPEN; //test
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
