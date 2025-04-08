/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_parser_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:34 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/08 17:52:28 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Validates if a zero ('0') character at position (y) in a line is 
 *        correctly placed based on surrounding characters.
 *
 * This function checks if the '0' character is surrounded by valid elements 
 * such as walls ('1'), players, doors ('D'), or other valid elements. It 
 * also ensures that '0' characters are not adjacent to invalid positions.
 * Special conditions are applied when the previous line contains a door ('D').
 *
 * @param line The current line in the map.
 * @param previous_line The previous line in the map for vertical validation.
 * @param y The current position (index) in the line.
 *
 * @return `true` if the '0' is valid, `false` otherwise.
 */
static bool	is_valid_zero(char *line, char *previous_line, int y)
{
	if (previous_line && previous_line[y])
	{
		if (previous_line[y] == ' ')
			return (false);
		if (previous_line[y] == 'D')
		{
			if (previous_line[y - 1] != '1' || previous_line[y + 1] != '1')
				return (false);
		}
	}
	if ((y > 0
			&& (line[y - 1] == '0'
				|| line[y - 1] == '1'
				|| ft_is_player(line[y - 1]) || line[y - 1] == 'D'
				|| line[y - 1] == 'X'))
		&& (line[y + 1] == '0'
			|| line[y + 1] == '1' || ft_is_player(line[y + 1])
			|| line[y + 1] == 'D'
			|| line[y + 1] == 'X'))
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Validates if the current space at position (y) in a line is valid 
 *        based on surrounding characters.
 *
 * This function checks if the current empty space (' ') is surrounded by walls 
 * ('1') or other empty spaces. It ensures that the space is properly placed 
 * within the grid, either at the beginning or surrounded by walls. It also 
 * checks vertical consistency using the previous line.
 *
 * @param line The current line in the map.
 * @param previous_line The previous line in the map (for vertical checks).
 * @param y The current position (index) in the line.
 *
 * @return `true` if the space is valid, `false` otherwise.
 */
static bool	is_valid_space(char *line, char *previous_line, int y)
{
	if (previous_line)
	{
		if (previous_line[y] && (previous_line[y] != ' '
				&& previous_line[y] != '1'))
		{
			return (false);
		}
	}
	if ((y > 0 && (line[y - 1] == ' ' || line[y - 1] == '1'))
		&& (line[y + 1] == ' ' || line[y + 1] == '1' || line[y + 1] == '\0'))
	{
		return (true);
	}
	if (y == 0 && (line[y] == ' ' || line[y] == '1'))
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Validates the edges of a line in the map for walls ('1') or spaces.
 *
 * This function checks if the first and last characters of a line are valid. 
 * If the line is marked as a "first or last" line, it must contain only walls 
 * ('1') or spaces (' '). For other lines, the function ensures that the first 
 * and last characters are walls ('1').
 *
 * @param line The line to check.
 * @param first_or_last Boolean flag indicating if the line is the first or last.
 *
 * @return `true` if the line edges are valid, `false` otherwise.
 */
static bool	is_valid_line_edges(char *line, bool first_or_last)
{
	int		len;
	char	*new_line;

	new_line = ft_strip(ft_strdup(line), 0);
	len = 0;
	while (new_line[len])
	{
		if (first_or_last && new_line[len] != '1' && new_line[len] != ' ')
		{
			free(new_line);
			return (false);
		}
		len++;
	}
	if (len == 0 || new_line[0] != '1' || new_line[len - 1] != '1')
	{
		free(new_line);
		return (false);
	}
	free(new_line);
	return (true);
}

/**
 * @brief Validates if a door ('D') is correctly placed in relation to walls 
 *        and players.
 *
 * This function ensures that when a door is found in the previous line, 
 * it is surrounded by walls ('0') or players ('P') in the current line. 
 * The door should be adjacent to valid positions (walls or players) for 
 * it to be considered valid.
 *
 * @param line The current line in the map.
 * @param previous_line The previous line in the map for vertical validation.
 * @param y The current position (index) in the line.
 *
 * @return `true` if the door is valid, `false` otherwise.
 */
bool	is_valid_wall_door(char *line, char *previous_line, int y)
{
	if (previous_line && previous_line[y])
	{
		if (previous_line[y] == 'D')
		{
			if ((previous_line[y - 1] == '0' || ft_is_player(line[y - 1])) && previous_line[y + 1] != '1')
				return (false);
			if ((previous_line[y + 1] == '0' || ft_is_player(line[y + 1])) && previous_line[y - 1] != '1')
				return (false);



				
			// if ((previous_line[y - 1] != '0' && !ft_is_player(line[y - 1]))
			// 	|| (previous_line[y + 1] != '0' && !ft_is_player(line[y + 1])))
			// 	return (false);
		}
	}
	return (true);
}

/**
 * @brief Validates a map wall line for proper structure and characters.
 * 
 * Checks whether a given line of a map wall is valid. It ensures that the 
 * edges of the line meet specific requirements, and verifies that '0' and 
 * ' ' characters are placed correctly according to predefined rules. The 
 * validation ensures the line adheres to the expected wall format.
 * 
 * @param line The map wall line to validate, as a null-terminated string.
 * @param previous_line The previous map line, used to validate continuity 
 * between walls.
 * @param first_or_last A boolean indicating if the line is the first or 
 * last in the map, used to adjust validation rules for edge lines.
 * @return true if the line is valid, false otherwise.
 */
bool	ft_valid_wall(char *line, char *previous_line, bool first_or_last)
{
	int	y;

	if (!is_valid_line_edges(line, first_or_last))
		return (false);
	y = 0;
	while (line[y])
	{
		if (line[y] == '0')
			if (y == 0 || line[y + 1] == '\0'
				|| !is_valid_zero(line, previous_line, y))
				return (false);
		if (line[y] == ' ')
			if (!is_valid_space(line, previous_line, y))
				return (false);
		if (line[y] == '1')
			if (!is_valid_wall_door(line, previous_line, y))
				return (false);
		y++;
	}
	return (true);
}
