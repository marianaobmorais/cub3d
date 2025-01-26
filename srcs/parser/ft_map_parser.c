#include "../../includes/cub3d.h"

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

static void	ft_add_texture(char *line, t_cub *cub, char *identifier, \
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
		return (ft_free_vector(tmp), free(line), ft_handle_error("Texture: too many arguments", cub));
	if (ft_strncmp(identifier, tmp[0], ft_strlen(tmp[0])) == 0)
	{
		filepath = ft_strip(ft_strdup(tmp[1]));
		ft_free_vector(tmp);
		if (!ft_is_ext(filepath, ".xpm"))
			return (free(filepath), ft_handle_error("Texture: File extension", cub));
		if (!ft_access(filepath))
			return (free(filepath), ft_handle_error("Texture: No such file/directory or permision", cub));
		if (direction == NORTH && !cub->map->north_texture)
			cub->map->north_texture = filepath;
		else if (direction == SOUTH && !cub->map->south_texture)
			cub->map->south_texture = filepath;
		else if (direction == WEST && !cub->map->west_texture)
			cub->map->west_texture = filepath;
		else if (direction == EAST && !cub->map->east_texture)
			cub->map->east_texture = filepath;
		else
			return (free(line), ft_handle_error("Texture: duplicate", cub));
		printf("Texture %s\n", identifier); //debug
	}
}

static void	ft_add_color(char *line, t_cub *cub, char *identifier, \
	t_directions direction)
{
	//TODO add brief
	char	*new_line;

	new_line = ft_strip(ft_strdup(line));
	if (ft_strncmp(identifier, new_line, 1) == 0 && !ft_isalpha(new_line[1]))
	{
		if (direction == FLOOR && !cub->map->floor_rgb)
		{
			cub->map->floor_rgb = malloc(sizeof(unsigned char) * 3);
			if (!cub->map->floor_rgb) // free(new_line);
				ft_handle_error("Malloc: floor_rgb", cub);
			ft_add_rgb(new_line, cub, cub->map->floor_rgb);
			// printf("%s [%d, %d, %d]\n", identifier, cub->map->floor_rgb[0],
			// 	cub->map->floor_rgb[1], cub->map->floor_rgb[2]); //debug
		}
		else if (direction == CEILING && !cub->map->ceiling_rgb)
		{
			cub->map->ceiling_rgb = malloc(sizeof(unsigned char) * 3);
			if (!cub->map->ceiling_rgb) //free(new_line);
				ft_handle_error("Malloc: ceiling_rgb", cub);
			ft_add_rgb(new_line, cub, cub->map->ceiling_rgb);
			// printf("%s [%d, %d, %d]\n", identifier, cub->map->ceiling_rgb[0],
			// 	cub->map->ceiling_rgb[1], cub->map->ceiling_rgb[2]); //debug
		}
		else
		{
			free(new_line);
			free(line);
			ft_handle_error("Color: duplicate", cub);
		}
	}
	free(new_line);
}


static char	*ft_buffer(char *buffer, char *line, int start, t_cub *cub)
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

static bool	ft_get_texture_color(char *line, t_cub *cub, int i)
{
	//TODO insert brief
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

void	ft_map_parser(int fd, t_cub *cub)
{
	char	*line;
	char	*buffer;
	int		i;

	i = 0;
	line = get_next_line(fd); //TODO separar logica
	if (!line)
		ft_handle_error("Map: empty", cub);
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
	if (!ft_validate_before(cub))
	{
		if (buffer)
			free(buffer);
		ft_handle_error("Map: missing arguments", cub);
	}
	cub->map->matrix = ft_split(buffer, '\n');
	free(buffer);
}
