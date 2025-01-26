#include "../../includes/cub3d.h"

static bool	ft_set_texture(t_cub *cub, char *filepath, t_directions direction)
{
	//TODO insert brief
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

void	ft_add_texture(char *line, t_cub *cub, char *identifier, \
	t_directions direction)
{
	//TODO add brief
	char	*new_line;
	char	**tmp;
	char	*filepath;

	new_line = ft_strip(ft_strdup(line));
	tmp = ft_split(new_line, ' ');
	free(new_line);
	if (tmp[2])
		return (ft_free_vector(tmp), free(line), ft_handle_error(MSG_TEXTURE, cub));
	if (ft_strncmp(identifier, tmp[0], ft_strlen(tmp[0])) == 0)
	{
		filepath = ft_strip(ft_strdup(tmp[1]));
		ft_free_vector(tmp);
		if (!ft_is_ext(filepath, ".xpm"))
			return (free(filepath), ft_handle_error(MSG_TEXTURE, cub)); //extension
		if (!ft_access(filepath))
			return (free(filepath), ft_handle_error(MSG_TEXTURE, cub)); // file
		if (!ft_set_texture(cub, filepath, direction))
			return (free(line), ft_handle_error(MSG_TEXTURE, cub)); //duplicate
	}
}

char	*ft_buffer(char *buffer, char *line, int start, t_cub *cub)
{
	//TODO add brief
	char	*tmp;

	if (ft_isempty(line) == 1 && start == 0)
	{
		free(line);
		free(buffer);
		ft_handle_error("Map: error new line", cub);
	}
	if (ft_isempty(line) == 1)
		return (NULL);
	tmp = ft_strjoin(buffer, line);
	free(buffer);
	return (tmp);
}
