#include "../../includes/cub3d.h"

/**
 * @brief Sets the texture filepath in the appropriate direction slot.
 *
 * This function assigns the given texture filepath to the corresponding 
 * direction (NORTH, SOUTH, WEST, EAST) in the map structure. If the 
 * texture for that direction has already been set, it returns `false`.
 * Otherwise, it successfully updates the texture and returns `true`.
 *
 * @param cub The main structure containing the game-related data.
 * @param filepath The texture filepath to assign.
 * @param direction The direction (NORTH, SOUTH, WEST, EAST) to set the texture.
 *
 * @return `true` if the texture was successfully set, or `false` if a texture 
 *         is already set for the given direction.
 */
static bool	ft_set_texture(t_cub *cub, char *filepath, t_directions direction)
{
	if (direction == NORTH && !cub->map->north_texture)
		cub->map->north_texture = filepath;
	else if (direction == SOUTH && !cub->map->south_texture)
		cub->map->south_texture = filepath;
	else if (direction == WEST && !cub->map->west_texture)
		cub->map->west_texture = filepath;
	else if (direction == EAST && !cub->map->east_texture)
		cub->map->east_texture = filepath;
	else
		return (false);
	return (true);
}

/**
 * @brief Adds a texture to the game by processing the given line.
 *
 * This function checks the validity of the texture line (e.g., file extension, 
 * file accessibility) and updates the game structure with the new texture. 
 * It handles errors such as incorrect file extensions, inaccessible files, 
 * and duplicates by returning an appropriate error code.
 *
 * @param line The line to process for adding the texture.
 * @param cub The main structure containing the game-related data.
 * @param identifier The texture identifier to check in the line.
 * @param direction The direction associated with the texture (e.g., NORTH, .).
 *
 * @return `ERROR` if an error is encountered, or `NO_BUFFER` if successful.
 */
t_parser_status	ft_add_texture(char *line, t_cub *cub, char *identifier, \
	t_directions direction)
{
	char	*new_line;
	char	**tmp;
	char	*filepath;

	new_line = ft_strip(ft_strdup(line), 0);
	tmp = ft_split(new_line, ' ');
	free(new_line);
	if (tmp[2])
		return (ft_free_vector(tmp), ERROR);
	if (ft_strncmp(identifier, tmp[0], ft_strlen(tmp[0])) == 0)
	{
		filepath = ft_strip(ft_strdup(tmp[1]), 0);
		ft_free_vector(tmp);
		if (!ft_is_ext(filepath, ".xpm"))
			return (free(filepath), ERROR); //ext
		if (!ft_access(filepath))
			return (free(filepath), ERROR); // file
		if (!ft_set_texture(cub, filepath, direction))
			return (free(filepath), ERROR); //duplicate
	}
	return (NO_BUFFER);
}

/**
 * @brief Buffers the content of a line and returns a new concatenated string.
 *
 * This function checks if the line is empty and handles errors accordingly. 
 * If the line is not empty, it concatenates the `buffer` and the `line`
 * into a new string and frees the previous `buffer`. If any error occurs
 * while handling the line, an error message is displayed.
 *
 * @param buffer The existing string buffer.
 * @param line The new line to be added to the buffer.
 * @param start A flag indicating the start of processing.
 * @param cub The main structure containing the game-related data.
 *
 * @return A new concatenated string or NULL if the line is empty.
 */
char	*ft_buffer(char *buffer, char *line, int start, t_cub *cub)
{
	char	*tmp;

	if (ft_is_empty(line) == 1 && start == 0)
	{
		free(line);
		line = NULL;
		free(buffer);
		buffer = NULL;
		ft_handle_error("Map: error new line", cub);
	}
	if (ft_is_empty(line) == 1)
		return (NULL);
	tmp = ft_strjoin(buffer, line);
	free(buffer);
	return (tmp);
}

/**
 * @brief Converts an RGB array to a hexadecimal color code.
 * 
 * This function takes an array of three unsigned chars representing the 
 * RGB (Red, Green, Blue) color values and converts it into a single 
 * hexadecimal color code. The resulting integer combines the RGB values 
 * in the standard format `0xRRGGBB`.
 * 
 * @param rgb An array of three unsigned chars, representing the RGB 
 * components of a color (with values between 0 and 255).
 * @return The corresponding hexadecimal color code as an integer.
 */
int	ft_arraytohex(unsigned char *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
