/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_parser_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:25 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/08 18:44:57 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Validates if a character is a valid map element.
 *
 * This function checks if the given character is one of the valid characters 
 * allowed in the map layout. Valid characters include walls ('1'), empty spaces 
 * ('0'), sprite ('S'), player orientations ('N', 'E', 'W'), doors ('D'), 
 * and special items ('X').
 *
 * @param c The character to be validated.
 *
 * @return `true` if the character is valid, `false` otherwise.
 */
static bool	ft_valid_char(char c)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'S' && c != 'N'
		&& c != 'E' && c != 'W' && c != 'D' && c != 'X')
		return (false);
	return (true);
}

/**
 * @brief Sets the player's position and direction on the map.
 * 
 * This function sets the player's position on the map by storing the
 * coordinates in the `player_squ_x` and `player_squ_y` variables. It also
 * determines the player's facing direction based on the character passed 
 * ('N', 'S', 'E', 'W'). The function ensures that the player is only 
 * placed once on the map.
 * 
 * @param c The character representing the player's direction ('N', 'S', 
 *          'E', or 'W').
 * @param cub The main structure holding map data.
 * @param x The x-coordinate (row) of the player on the map.
 * @param y The y-coordinate (column) of the player on the map.
 * @return true if the player's position and direction were successfully 
 *         set, false if the player was already placed on the map.
 */
static bool	ft_set_player(char c, t_cub *cub, int x, int y)
{
	if (cub->map->player_squ_x == -1)
	{
		cub->map->player_squ_x = y;
		cub->map->player_squ_y = x;
		if (c == 'S')
			cub->map->direction = SOUTH;
		if (c == 'N')
			cub->map->direction = NORTH;
		if (c == 'E')
			cub->map->direction = EAST;
		if (c == 'W')
			cub->map->direction = WEST;
	}
	else
		return (false);
	return (true);
}

/**
 * @brief Checks if a line in the map is valid based on character rules and 
 *        processes any players, sprites, or doors.
 *
 * This function validates each character in the line, ensuring it is a valid 
 * map element. If the character represents a player, sprite, or door, the 
 * function also checks if its position is valid and sets the corresponding 
 * object in the map structure. Invalid characters or invalid positions for 
 * sprites or doors will cause the function to return `false`.
 *
 * @param line The current line in the map.
 * @param previous_line The previous line in the map for vertical validation.
 * @param y The current position (index) of the line in the map.
 * @param cub The main game structure containing the map data.
 *
 * @return `true` if the line is valid, `false` otherwise.
 */
static bool	ft_check_line(char *line, char *previous_line, int y, t_cub *cub)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!ft_valid_char(line[x]))
			return (false);
		if (ft_is_player(line[x]))
			if (!ft_set_player(line[x], cub, x, y))
				return (false);
		if (line[x] == 'X')
		{
			if (!is_valid_sprite(line, previous_line, x))
				return (false);
			ft_set_sprite(cub, x, y);
		}
		if (line[x] == 'D')
			ft_set_door(cub, x, y);
		x++;
	}
	return (true);
}

static bool	is_valid_door(t_cub *cub, char **matrix)
{
  //add brief
	t_ipoint	tile;
	int			openings;
	int			i;

	i = 0;
	while (i < cub->map->door_count)
	{
		tile.x = cub->map->door[i].tile.x;
		tile.y = cub->map->door[i].tile.y;
		openings = 0;
		if (matrix[tile.x + 1][tile.y] == '0')
			openings++;
		if (matrix[tile.x - 1][tile.y] == '0')
			openings++;
		if (matrix[tile.x][tile.y + 1] == '0')
			openings++;
		if (matrix[tile.x][tile.y - 1] == '0')
			openings++;
		printf("[%d] y %d x %d -> openings %d \n", i, tile.y, tile.x, openings);
		if (openings != 1)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Parses the map matrix and validates the map's structure.
 * 
 * This function iterates through each line of the map matrix, checking if 
 * the characters in each line are valid using `ft_check_line`. It also 
 * validates the wall structure and player position using `ft_valid_wall` 
 * and `ft_set_player`. If any issues are found, an error message is raised.
 * 
 * @param cub The main structure holding the map data.
 * @param matrix The map matrix to be parsed, represented as an array of strings.
 * @return void
 */
void	ft_matrix_parser(t_cub *cub, char **matrix)
{
	int		y;
	bool	first_or_last;
	char	*line;
	char	*previous_line;

	y = 0;
	previous_line = NULL;
	while (matrix[y])
	{
		first_or_last = false;
		if (y == 0 || y + 1 == cub->map->height)
			first_or_last = true;
		line = matrix[y];
		if (y > 0)
			previous_line = matrix[y - 1];
		if (!ft_check_line(line, previous_line, y, cub))
			ft_handle_error(MSG_MAP, cub);
		if (!ft_valid_wall(line, previous_line, first_or_last))
			ft_handle_error(MSG_MAP, cub);
		y++;
	}
	if (!is_valid_door(cub, matrix))
		ft_handle_error(MSG_MAP, cub);
	if (cub->map->player_squ_x == -1)
		ft_handle_error(MSG_MAP, cub);
}
