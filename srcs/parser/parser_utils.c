/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:17 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/22 18:55:18 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Checks if a file is accessible for reading.
 * 
 * Attempts to open the specified file in read-only mode to determine whether 
 * it is accessible. If the file can be opened successfully, it is considered 
 * accessible.
 * 
 * @param filepath The path to the file to check, as a null-terminated string.
 * @return true if the file is accessible for reading, false otherwise.
 */
bool	ft_access(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

/**
 * @brief Checks if a filename has a specific file extension.
 * 
 * Verifies whether the given filename ends with the specified file extension. 
 * The comparison is case-sensitive and ensures the extension matches exactly 
 * at the end of the filename.
 * 
 * @param filename The name of the file to check, as a null-terminated string.
 * @param ext The expected file extension, as a null-terminated string.
 * @return true if the filename ends with the specified extension, 
 *         false otherwise.
 */
bool	ft_is_ext(char *filename, char *ext)
{
	char	*file_ext;

	file_ext = ft_strnstr(filename, ext, ft_strlen(filename));
	if (!file_ext || ft_strlen(file_ext) != ft_strlen(ext))
	{
		return (false);
	}
	return (true);
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

/* DEBUG */
void	ft_print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("Player x=%d y=%d, ", map->player_squ_x, map->player_squ_y);
	printf("direction: %s\n\n",
			(map->direction == NORTH) ? "N" :
			(map->direction == SOUTH) ? "S" :
			(map->direction == WEST) ? "W" :
			(map->direction == EAST) ? "E" : "x");
	if (map->matrix)
	{
		while (map->matrix[i])
		{
			printf("[%d] |%s|\n", i, map->matrix[i]);
			i++;
		}
	}
	printf("\n");
}
