#include "../../includes/cub3d.h"

/**
 * @brief Parses and assigns RGB values from a color definition line.
 * 
 * Extracts and validates the RGB components from the given line, ensuring 
 * they are numeric values within the valid range (0-255). The function splits 
 * the line by commas and checks that there are exactly three valid components 
 * before assigning them to the provided RGB array. If any error occurs, 
 * the function triggers an error and cleans up resources.
 * 
 * @param line The input line containing the RGB color definition.
 * @param cub A pointer to the game structure (t_cub) to handle errors.
 * @param rgb A pointer to the array where the RGB components will be stored.
 */
static void	ft_add_rgb(char *line, t_cub *cub, unsigned char *rgb)
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
				ft_handle_error(MSG_COLOR, cub)); //arguments
		ft_strip(tmp[i]);
		if (!ft_isnumeric(tmp[i]))
			return (free(line), ft_free_vector(tmp), \
				ft_handle_error(MSG_COLOR, cub)); //numeric
		nbr = ft_atoi(tmp[i]);
		if (nbr < 0 || nbr > 255)
			return (free(line), ft_free_vector(tmp), \
				ft_handle_error(MSG_COLOR, cub)); //range
		rgb[i] = nbr;
		i++;
	}
	ft_free_vector(tmp);
	if (i < 3)
		return (free(line), ft_handle_error(MSG_COLOR, cub)); //arguments
}

/**
 * @brief Processes and assigns RGB color values for the floor or ceiling.
 * 
 * Parses the given line to extract RGB values for either the floor or ceiling 
 * of the game map, based on the specified identifier and direction.
 * The function ensures that the color is assigned only once for each of the
 * floor and ceiling. 
 * It also handles memory allocation for the RGB values and validates the input.
 * If any errors are encountered, an error message is triggered and resources 
 * are freed.
 * 
 * @param line The input line containing the color definition.
 * @param cub A pointer to the game structure (t_cub) to handle errors.
 * @param identifier The identifier used to check the color type
 *        (e.g., "F" for floor, "C" for ceiling).
 * @param direction The direction for which the color will be assigned
 *        (FLOOR or CEILING).
 */
static void	ft_add_color(char *line, t_cub *cub, char *identifier, \
	t_directions direction)
{
	char	*new_line;

	new_line = ft_strip(ft_strdup(line));
	if (ft_strncmp(identifier, new_line, 1) == 0 && !ft_isalpha(new_line[1]))
	{
		if (direction == FLOOR && !cub->map->floor_rgb)
		{
			cub->map->floor_rgb = malloc(sizeof(unsigned char) * 3);
			if (!cub->map->floor_rgb)
				return (free(new_line), ft_handle_error("Malloc", cub));
			ft_add_rgb(new_line, cub, cub->map->floor_rgb);
		}
		else if (direction == CEILING && !cub->map->ceiling_rgb)
		{
			cub->map->ceiling_rgb = malloc(sizeof(unsigned char) * 3);
			if (!cub->map->ceiling_rgb)
				return (free(new_line), ft_handle_error("Malloc", cub));
			ft_add_rgb(new_line, cub, cub->map->ceiling_rgb);
		}
		else
			return (free(new_line), free(line), \
				ft_handle_error(MSG_COLOR, cub)); //duplicate
	}
	free(new_line);
}

/**
 * @brief Parses a line to extract and assign texture or color values.
 * 
 * Checks the provided line for specific identifiers (e.g., "NO", "SO", "WE", 
 * "EA" for textures or "F", "C" for floor and ceiling colors) and calls the 
 * appropriate functions to assign textures or colors to the game map.
 * The function also validates the line and ensures the correct order
 * of texture and color definitions. 
 * If the line contains an invalid or unrecognized identifier, the function
 * triggers an error.
 * 
 * @param line The input line containing the texture or color definition.
 * @param cub A pointer to the game structure (t_cub) where the textures and 
 *            colors will be stored.
 * @param i The index of the line in the map configuration, used for order 
 *          validation.
 * @return true if the line was successfully processed, false otherwise.
 */
static bool	ft_get_texture_color(char *line, t_cub *cub, int i)
{
	if (ft_isempty(line) == 1)
		return (false);
	else if (ft_strnstr(line, "NO", ft_strlen(line)))
		ft_add_texture(line, cub, "NO", NORTH);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		ft_add_texture(line, cub, "SO", SOUTH);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		ft_add_texture(line, cub, "WE", WEST);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		ft_add_texture(line, cub, "EA", EAST);
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		ft_add_color(line, cub, "F", FLOOR);
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		ft_add_color(line, cub, "C", CEILING);
	else
	{
		if (i == 0)
			ft_handle_error("Map: invalid order", cub);
		return (false);
	}
	return (true);
}

/**
 * @brief Checks if all the required map textures and colors are set.
 * 
 * Verifies whether all the necessary textures (north, south, west, east) 
 * and color values (ceiling and floor) have been assigned to the map. If 
 * any of the required values are missing, the function returns false,
 * indicating that the map is not fully configured. Otherwise, it returns true.
 * 
 * @param cub A pointer to the game structure (t_cub) containing the map data.
 * @return true if all required textures and colors are set, false otherwise.
 */
static bool	ft_isfilled(t_cub *cub)
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

/**
 * @brief Parses the map configuration file and extracts texture and color data.
 * 
 * Reads each line from the map file and processes it to extract texture and 
 * color information using the `ft_get_texture_color` function. Valid lines 
 * related to textures and colors are processed, while other lines are
 * accumulated in a buffer for further processing. Once all lines are read, 
 * the function verifies that all required textures and colors are set using
 * `ft_isfilled`. 
 * If any required data is missing, an error is triggered. Finally,
 * the buffered map data is split into a matrix representing the map structure.
 * 
 * @param fd The file descriptor of the map file to parse.
 * @param cub A pointer to the game structure (t_cub) to store the parsed map
 *        data.
 */
void	ft_map_parser(int fd, t_cub *cub)
{
	char	*line;
	char	*buffer;
	int		i;

	i = 0;
	buffer = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_get_texture_color(line, cub, i))
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
	if (!ft_isfilled(cub))
		return (free(buffer), ft_handle_error(MSG_MAP, cub)); //arguments
	return (cub->map->matrix = ft_split(buffer, '\n'), free(buffer));
}
