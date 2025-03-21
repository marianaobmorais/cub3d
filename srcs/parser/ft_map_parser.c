#include "../../includes/cub3d.h"

/**
 * @brief Adds RGB color values to the specified color channel (floor/ceiling).
 *
 * This function processes a line that contains RGB values (in the format of
 * `R,G,B`) and stores them in the provided `rgb` array. The RGB values must
 * be numeric and within the valid range of 0 to 255.
 *
 * @param line The line containing the RGB values.
 * @param cub The main struct containing the game-related data (not used here).
 * @param rgb The array to store the RGB values (3 elements: R, G, B).
 *
 * @return A status code indicating the result of the operation.
 *         Possible values: `NO_BUFFER`, `ERROR`.
 */
static t_parser_status	ft_add_rgb(char *line, unsigned char *rgb)
{
	char	**tmp;
	int		nbr;
	int		i;

	i = 0;
	tmp = ft_split(line + 1, ',');
	while (tmp[i])
	{
		if (i > 2)
			return (free(line), ft_free_vector(tmp), ERROR); //arguments
		ft_strip(tmp[i], 0);
		if (!ft_isnumeric(tmp[i]))
			return (free(line), ft_free_vector(tmp), ERROR); //numeric
		nbr = ft_atoi(tmp[i]);
		if (nbr < 0 || nbr > 255)
			return (free(line), ft_free_vector(tmp), ERROR); //range
		rgb[i] = nbr;
		i++;
	}
	ft_free_vector(tmp);
	if (i < 3)
		return (free(line), ERROR); //arguments
	return (free(line), NO_BUFFER);
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
			return (ft_add_rgb(new_line, cub->map->floor_rgb));
		}
		else if (direction == CEILING && !cub->map->ceiling_rgb)
		{
			cub->map->ceiling_rgb = malloc(sizeof(unsigned char) * 3);
			if (!cub->map->ceiling_rgb)
				return (free(new_line), ERROR);
			return (ft_add_rgb(new_line, cub->map->ceiling_rgb));
		}
		else
			return (free(new_line), ERROR);
	}
	free(new_line);
	return (NO_BUFFER);
}

/**
 * @brief Parses a line to get texture or color data for the map.
 *
 * This function checks a given line to identify whether it defines a texture
 * for any of the four map directions (North, South, West, East) or the floor
 * and ceiling colors. Based on the identifier in the line, it calls the
 * appropriate function to process the texture or color data.
 *
 * @param line The line to be parsed.
 * @param cub The main structure containing the game-related data.
 * @param i An index to determine if the line is the first to be processed.
 *
 * @return A status code indicating the result of the parsing. 
 *         Possible values: `NO_BUFFER`, `BUFFER`, `ERROR`.
 */
static t_parser_status	ft_get_texture_color(char *line, t_cub *cub, int i)
{
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
		{
			return (ERROR);
		}
		return (BUFFER);
	}
	return (NO_BUFFER);
}

/**
 * @brief Checks if all required map data is filled.
 *
 * This function checks whether all the required fields (textures for all four 
 * directions and the ceiling and floor colors) in the map structure are filled.
 * It returns `true` if all fields are filled, and `false` if any are missing.
 *
 * @param cub The main structure containing the game-related data.
 *
 * @return `true` if all required map data is filled, or `false` if any 
 *         required data is missing.
 */
static void	ft_isfilled(t_cub *cub, char *buffer)
{
	if (!cub->map->north_texture || !cub->map->south_texture
		|| !cub->map->west_texture || !cub->map->east_texture
		|| !cub->map->ceiling_rgb || !cub->map->floor_rgb)
		return (free(buffer), ft_handle_error(MSG_MAP, cub)); //arguments
}

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
	ft_isfilled(cub, buffer);
	cub->map->matrix_tmp = ft_split(buffer, '\n');
	return (ft_fill_matrix(cub), free(buffer));
}
