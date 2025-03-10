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
 * @brief Checks if a character is a whitespace character.
 * 
 * Determines whether the given character is a whitespace character, including 
 * space (' ') and other control characters like tab, newline, vertical tab, 
 * form feed, and carriage return.
 * 
 * @param c The character to check, represented as an int.
 * @return 1 if the character is a whitespace character, or 0 otherwise.
 */
int	ft_isspace(int c, int mode)
{
	//update brief
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
 * @brief Removes leading and trailing whitespace from a string in place.
 * 
 * Trims leading and trailing whitespace characters from the given string, 
 * modifying it directly. The function ensures the resulting string is 
 * null-terminated and handles empty or fully whitespace strings correctly.
 * 
 * @param str The string to be stripped, as a null-terminated char array. 
 *            If the string is NULL or empty, it is returned unchanged.
 * @return A pointer to the modified string.
 */
char	*ft_strip(char *str, int mode)
{
	//update brief
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

int	ft_arraytohex(unsigned char *rgb)
{
	//brief
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
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
			(map->direction == WEST) ? "W" : "E");
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
