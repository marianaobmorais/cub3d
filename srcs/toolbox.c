#include "../includes/cub3D.h"

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
int	ft_isspace(int c)
{
	if ((c == 32) || (c > 8 && c < 14))
		return (1);
	else
		return (0);
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
char	*ft_strip(char *str)
{
	int		start;
	int		end;
	int		i;

	if (!str || *str == '\0')
		return (str);
	end = ft_strlen(str) - 1;
	while (end >= 0 && ft_isspace(str[end]))
		str[end--] = '\0';
	if (end < 0)
		return (str);
	start = 0;
	while (ft_isspace(str[start]))
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
 * @brief Frees all strings in a vector (array of strings) and the vector
 *        itself.
 *
 * This function iterates through the array of strings (vector), freeing each
 * string individually. After all strings are freed, the function frees the
 * vector pointer itself to prevent memory leaks.
 *
 * @param vector A pointer to the array of strings to be freed.
 */
void	ft_free_vector(char **vector)
{
	int	i;

	i = 0;
	if (vector)
	{
		while (vector[i])
		{
			free(vector[i]);
			i++;
		}
		free(vector);
	}
}

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

void	ft_add_rgb(char *line, t_cub *cub, unsigned char *rgb)
{
	char	**tmp;
	int		nbr;
	int		i;

	i = 0;
	tmp = ft_split(line + 1, ',');
	while (tmp[i])
	{
		if (i > 2)
			return (free(line), ft_free_vector(tmp), \
				ft_handle_error("Color: too many arguments", cub));
		ft_strip(tmp[i]);
		if (!ft_isnumeric(tmp[i]))
			return (free(line), ft_free_vector(tmp), \
				ft_handle_error("Color: no numeric", cub));
		nbr = ft_atoi(tmp[i]);
		if (nbr < 0 || nbr > 255)
			return (free(line), ft_free_vector(tmp), \
				ft_handle_error("Color: without range RGB", cub));
		rgb[i] = nbr;
		i++;
	}
	if (i < 3)
		return (free(line), ft_free_vector(tmp), \
			ft_handle_error("Color: missing arguments", cub));
	ft_free_vector(tmp);
}

bool	ft_validate_before(t_cub *cub)
{
	if (!cub->map->north_texture)
		return (false);
	if (!cub->map->south_texture)
		return (false);
	if (!cub->map->west_texture)
		return (false);
	if (!cub->map->east_texture)
		return (false);
	if (!cub->map->ceiling_rgb)
		return (false);
	if (!cub->map->floor_rgb)
		return (false);
	return (true);
}
