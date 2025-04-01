/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:17 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/01 20:46:31 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Checks if a character represents a player in the map.
 *
 * This function validates if the given character corresponds to a player 
 * based on the possible player orientations ('N', 'S', 'E', 'W'). If the 
 * character matches one of these orientations, it returns `true`, indicating 
 * the presence of a player at that position.
 *
 * @param c The character to be checked.
 *
 * @return `true` if the character is a player ('N', 'S', 'E', or 'W'), 
 *         `false` otherwise.
 */
bool	ft_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'N')
		return (true);
	else
		return (false);
}

/**
 * @brief Checks if a string contains only numeric characters.
 * 
 * Verifies whether the given string consists exclusively of digits (0-9). 
 * The function iterates over each character in the string and checks if each 
 * one is a valid digit. If any non-digit character is found, the function 
 * returns false.
 * 
 * @param nbr The string to check, as a null-terminated char array.
 * @return 1 if the string is entirely numeric, 0 otherwise.
 */
int	ft_isnumeric(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks if a character is a space or a whitespace character.
 * 
 * This function determines whether a given character is a space (' ') or
 * a control character like tab, newline, or carriage return, depending on 
 * the specified mode. In mode 0, it checks for both spaces and control 
 * characters. In mode 1, it only checks for control characters.
 * 
 * @param c The character to check.
 * @param mode The mode to specify which characters to check for (0 for space 
 * and control characters, 1 for only control characters).
 * @return 1 if the character is a space or whitespace character, 0 otherwise.
 */
int	ft_isspace(int c, int mode)
{
	if (mode == 0)
	{
		if ((c == 32) || (c > 8 && c < 14))
			return (1);
		else
			return (0);
	}
	else
	{
		if (c > 8 && c < 14)
			return (1);
		else
			return (0);
	}
}

/**
 * @brief Strips whitespace characters from the beginning and end of a string.
 * 
 * This function removes leading and trailing whitespace characters from 
 * the given string. The characters considered as whitespace are determined 
 * by the `ft_isspace` function, and the behavior can be modified using the 
 * `mode` parameter. If the `mode` is 0, it removes spaces, tabs, and other 
 * control characters. If the `mode` is 1, it only removes control characters.
 * 
 * @param str The string to strip, modified in place.
 * @param mode The mode determining which characters to strip (0 for space 
 * and control characters, 1 for only control characters).
 * @return The modified string with leading and trailing whitespace removed.
 */
char	*ft_strip(char *str, int mode)
{
	int		start;
	int		end;
	int		i;

	if (!str || *str == '\0')
		return (str);
	end = ft_strlen(str) - 1;
	while (end >= 0 && ft_isspace(str[end], mode))
		str[end--] = '\0';
	if (end < 0)
		return (str);
	start = 0;
	while (ft_isspace(str[start], mode))
		start++;
	if (start > 0)
	{
		i = 0;
		while (str[start + i] != '\0')
		{
			str[i] = str[start + i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

/**
 * @brief Checks if a given string is empty or consists only of whitespace.
 * 
 * Determines whether the input string is NULL, empty, or contains only 
 * whitespace characters. The function creates a stripped copy of the input 
 * string to perform the check, ensuring the original string remains unaltered.
 * 
 * @param line The string to check, as a null-terminated char array. 
 *             Can be NULL.
 * @return 1 if the string is NULL, empty, or consists only of whitespace, 
 *         0 otherwise.
 */
int	ft_is_empty(char *line)
{
	char	*tmp;

	if (!line)
		return (1);
	tmp = ft_strip(ft_strdup(line), 0);
	if (!tmp)
		return (1);
	if (tmp[0] == '\0')
		return (free(tmp), 1);
	return (free(tmp), 0);
}

// /* DEBUG */
// void	ft_print_map(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	printf("Player x=%d y=%d, ", map->player_squ_x, map->player_squ_y);
// 	printf("direction: %s\n\n",
// 			(map->direction == NORTH) ? "N" :
// 			(map->direction == SOUTH) ? "S" :
// 			(map->direction == WEST) ? "W" :
// 			(map->direction == EAST) ? "E" : "x");
// 	if (map->matrix)
// 	{
// 		while (map->matrix[i])
// 		{
// 			printf("[%d] |%s|\n", i, map->matrix[i]);
// 			i++;
// 		}
// 	}
// 	printf("\n");
// }
