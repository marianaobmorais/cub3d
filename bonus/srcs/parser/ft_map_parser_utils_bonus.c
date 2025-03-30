/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:07 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/30 16:30:30 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
			return (free(filepath), ERROR);
		if (!ft_access(filepath))
			return (free(filepath), ERROR);
		if (!ft_set_texture(cub, filepath, direction))
			return (free(filepath), ERROR);
	}
	return (NO_BUFFER);
}

/**
 * ft_buffer - Appends a line to the existing map buffer or handles empty
 * lines that appear after the map has started.
 *
 * @buffer: Current map buffer (may be NULL on first call).
 * @line: Line to append to the buffer.
 * @start: Indicates if this is the beginning of the map (1 if true).
 * @cub: Pointer to the main game struct, used for error handling and file
 *       access.
 *
 * If an empty line appears after the map has started (start == 0), the
 * function frees all resources, skips remaining lines, and throws an error.
 *
 * Returns the updated buffer with the new line appended, or NULL on error.
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
		line = get_next_line(cub->fd);
		while (line)
		{
			free(line);
			line = get_next_line(cub->fd);
		}
		ft_handle_error("Map: error new line", cub);
	}
	if (ft_is_empty(line) == 1)
		return (NULL);
	ft_count_sprites(cub, line);
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

/**
 * ft_safe_split - Safely splits the map buffer into lines.
 *
 * @buffer: Map buffer containing the full map as a string.
 * @cub: Pointer to the main game struct, used for error handling.
 *
 * If the buffer is NULL, triggers an error. Otherwise, splits the buffer
 * into an array of strings using newline as the delimiter.
 *
 * Returns the resulting array of strings (map matrix).
 */
char	**ft_safe_split(char *buffer, t_cub *cub)
{
	if (!buffer)
		ft_handle_error(MSG_MAP, cub);
	return (ft_split(buffer, '\n'));
}
