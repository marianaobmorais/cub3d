#include "../../includes/cub3d.h"

/**
 * @brief Determines the dimensions of the matrix (height and width).
 *
 * This function calculates the height and width of the matrix represented by 
 * the `matrix_tmp` array. The height is the number of rows, and the width is
 * the length of the longest row. These values are stored in the `map`
 * structure for further use.
 *
 * @param cub The main structure containing the map data.
 */
static void	matrix_dimensions(t_cub *cub)
{
	size_t	tmp;
	size_t	height;
	size_t	width;

	height = 0;
	width = ft_strlen(cub->map->matrix_tmp[height]);
	while (cub->map->matrix_tmp[height])
	{
		tmp = ft_strlen(cub->map->matrix_tmp[height]);
		if (tmp > width)
			width = tmp;
		(height)++;
	}
	cub->map->height = (int) height;
	cub->map->width = (int) width;
}

/**
 * @brief Fills a line of the matrix to match the required width.
 *
 * This function takes a line of characters, ensuring that the line has a 
 * length equal to the specified `width`. If the line is shorter than the 
 * required width, it pads the line with spaces. If the line is longer, it 
 * truncates it. The resulting line is returned as a new string.
 *
 * @param line The original line to be processed.
 * @param width The desired width for the new line.
 * @return A new string that is filled to the specified width.
 */
static char	*fill_line(char *line, int width)
{
	char	*new_line;
	int		i;
	int		limit;

	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char) * (width + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	limit = (int) ft_strlen(line);
	while (i < width)
	{
		if (i < limit)
			new_line[i] = line[i];
		else
			new_line[i] = ' ';
		i++;
	}
	new_line[width] = '\0';
	free(line);
	return (new_line);
}

/**
 * @brief Fills the matrix with the map data after processing.
 *
 * This function initializes the `matrix` field of the `cub->map` structure by
 * allocating memory for a new matrix and copying the map data from a temporary
 * matrix (`matrix_tmp`). It processes each line by stripping unnecessary
 * characters and then fills each line using the `fill_line` function. The
 * matrix dimensions are determined before filling the matrix.
 *
 * @param cub Pointer to the main game structure.
 */
void	ft_fill_matrix(t_cub *cub)
{
	int		i;
	char	**new_matrix;
	char	*line;

	matrix_dimensions(cub);
	new_matrix = (char **) malloc(sizeof(char *) * (cub->map->height + 1));
	if (!new_matrix)
		ft_handle_error("malloc: fill matrix new matrix", cub);
	i = 0;
	while (cub->map->matrix_tmp[i])
	{
		line = ft_strip(ft_strdup(cub->map->matrix_tmp[i]), 1);
		new_matrix[i] = fill_line(line, cub->map->width);
		if (!(new_matrix[i]))
			ft_handle_error("malloc: fill matrix new matrix", cub);
		i++;
	}
	new_matrix[i] = NULL;
	cub->map->matrix = new_matrix;
}
