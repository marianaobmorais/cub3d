#include "../../includes/cub3d.h"

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

void	ft_fill_matrix(t_cub *cub)
{
	int		i;
	char	**new_matrix;
	char	*line;

	matrix_dimensions(cub);
	printf("width-> %d | height-> %d \n", cub->map->width, cub->map->height); //debug
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
	ft_print_map(cub->map);
	// adicionar ' ' para completar o que falta para ser igual ao width
}
