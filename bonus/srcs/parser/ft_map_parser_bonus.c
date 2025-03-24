/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:42 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/22 19:29:36 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * ft_add_rgb - Parses a line to extract RGB values and stores them.
 *
 * @line: Line containing the RGB values, expected in "R,G,B" format.
 * @rgb: Pointer to an RGB array (allocated beforehand).
 *
 * Splits the line by commas, validates each number (0–255), and stores it in
 * the RGB array. If the format is invalid or values are out of range, frees
 * all allocated memory and returns ERROR.
 *
 * Returns NO_BUFFER on success, or ERROR on failure.
 */
static t_parser_status	ft_add_rgb(char *line, unsigned char **rgb)
{
	char	**tmp;
	int		nbr;
	int		i;

	i = 0;
	tmp = ft_split(line + 1, ',');
	while (tmp[i])
	{
		if (i > 2)
			return (free(line), ft_free_vector(tmp), ERROR);
		ft_strip(tmp[i], 0);
		if (!ft_isnumeric(tmp[i]))
			return (free(line), ft_free_vector(tmp), ERROR);
		nbr = ft_atoi(tmp[i]);
		if (nbr < 0 || nbr > 255)
			return (free(line), ft_free_vector(tmp), ERROR);
		(*rgb)[i++] = (unsigned int) nbr;
	}
	if (i < 3)
	{
		free(*rgb);
		*rgb = NULL;
		return (ft_free_vector(tmp), free(line), ERROR);
	}
	return (ft_free_vector(tmp), free(line), NO_BUFFER);
}

/**
 * @brief Adds color information (floor or ceiling) to the map structure.
 *
 * This function processes a line that specifies a floor or ceiling color and
 * stores the RGB values in the appropriate field of the `cub` structure. It
 * also checks if the color data has already been set for the floor or ceiling.
 *
 * @param line The line containing the color data.
 * @param cub The main structure containing the game-related data.
 * @param identifier A string identifier ("F" or "C") for the color type.
 * @param direction The color direction (FLOOR or CEILING).
 *
 * @return A status code indicating the result of the operation.
 *         Possible values: `NO_BUFFER`, `ERROR`.
 */
static t_parser_status	ft_add_color(char *line, t_cub *cub, char *identifier, \
	t_directions direction)
{
	char	*new_line;

	new_line = ft_strip(ft_strdup(line), 0);
	if (ft_strncmp(identifier, new_line, 1) == 0 && !ft_isalpha(new_line[1]))
	{
		if (direction == FLOOR && !cub->map->floor_rgb)
		{
			cub->map->floor_rgb = malloc(sizeof(unsigned char) * 3);
			if (!cub->map->floor_rgb)
				return (free(new_line), ERROR);
			return (ft_add_rgb(new_line, &cub->map->floor_rgb));
		}
		else if (direction == CEILING && !cub->map->ceiling_rgb)
		{
			cub->map->ceiling_rgb = malloc(sizeof(unsigned char) * 3);
			if (!cub->map->ceiling_rgb)
				return (free(new_line), ERROR);
			return (ft_add_rgb(new_line, &cub->map->ceiling_rgb));
		}
		else
			return (free(new_line), ERROR);
	}
	free(new_line);
	return (NO_BUFFER);
}

/**
 * ft_isfilled - Checks if all required map information has been set.
 *
 * @cub: Pointer to the main game struct.
 * @buffer: Buffer to be freed if an error occurs (can be NULL).
 * @mode: If 1, return false silently. If 0, free buffer, print error, and
 *        return false.
 *
 * Returns true if all required textures and colors are filled in the map;
 * otherwise returns false, optionally triggering an error.
 */
static bool	ft_isfilled(t_cub *cub, char *buffer, int mode)
{
	if (!cub->map->north_texture || !cub->map->south_texture
		|| !cub->map->west_texture || !cub->map->east_texture
		|| !cub->map->ceiling_rgb || !cub->map->floor_rgb)
	{
		if (mode == 1)
			return (false);
		else
		{
			return (free(buffer), ft_handle_error(MSG_MAP, cub), false);
		}
	}
	return (true);
}

/**
 * ft_get_texture_color - Parses a line to extract texture or color info and
 * stores it in the game's main struct.
 *
 * @line: Line read from the configuration file.
 * @cub: Pointer to the main game struct.
 * @i: Index of the current line, used to control error handling.
 *
 * Returns a parser status indicating whether the line was valid, should be
 * buffered, or an error occurred.
 */

static t_parser_status	ft_get_texture_color(char *line, t_cub *cub, int i)
{
	if (ft_is_empty(line) == 1 && ft_isfilled(cub, NULL, 1) == true)
		return (BUFFER);
	if (ft_is_empty(line) == 1)
		return (NO_BUFFER);
	else if (ft_strnstr(line, "NO", ft_strlen(line)))
		return (ft_add_texture(line, cub, "NO", NORTH));
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		return (ft_add_texture(line, cub, "SO", SOUTH));
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		return (ft_add_texture(line, cub, "WE", WEST));
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		return (ft_add_texture(line, cub, "EA", EAST));
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		return (ft_add_color(line, cub, "F", FLOOR));
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		return (ft_add_color(line, cub, "C", CEILING));
	else
	{
		if (i == 0)
			return (ERROR);
		return (BUFFER);
	}
	return (NO_BUFFER);
}

/**
 * ft_map_parser - Parses the configuration file, extracting textures, colors,
 * and the map layout. Buffers map lines and fills the map matrix.
 *
 * @fd: File descriptor of the configuration file.
 * @cub: Pointer to the main game struct.
 * @i: Line index used to help control error behavior during parsing.
 *
 * Reads each line from the file, processes texture/color identifiers, and
 * buffers map content. Verifies that required elements are present before
 * converting the map into a matrix.
 */
void	ft_map_parser(int fd, t_cub *cub, int i)
{
	char			*line;
	char			*buffer;
	t_parser_status	status;

	buffer = NULL;
	line = get_next_line(fd);
	status = NO_BUFFER;
	while (line)
	{
		if (status != ERROR)
			status = ft_get_texture_color(line, cub, i);
		if (status == BUFFER)
		{
			if (!buffer)
				buffer = ft_buffer(buffer, line, 1, cub);
			else
				buffer = ft_buffer(buffer, line, 0, cub);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	ft_isfilled(cub, buffer, 0);
	cub->map->matrix_tmp = ft_safe_split(buffer, cub);
	return (ft_fill_matrix(cub), free(buffer));
}
