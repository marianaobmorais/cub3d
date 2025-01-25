#include "../includes/cub3D.h"

static bool	ft_map_parser(char *line, t_cub *cub, int i)
{
	//TODO insert brief
	if (ft_isempty(line) == 1)
		return (true);
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

static void	ft_init_map(int fd, t_cub *cub)
{
	//TODO insert brief
	char	*buffer;
	char	*line;
	int		i;
	i = 0;
	buffer = NULL;
	cub->map = (t_map *) malloc(sizeof(t_map));
	if (!cub->map)
		ft_handle_error("Malloc: t_map", cub);
	cub->map->matrix = NULL;
	cub->map->north_texture = NULL;
	cub->map->south_texture = NULL;
	cub->map->west_texture = NULL;
	cub->map->east_texture = NULL;
	cub->map->floor_rgb = NULL;
	cub->map->ceiling_rgb = NULL;
	line = get_next_line(fd); //TODO separar logica
	if (!line)
		ft_handle_error("Map: empty", cub);
	while (line)
	{
		if (!ft_map_parser(line, cub, i))
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
	//TODO all check inside on ft map parser
}

void ft_loadmap(char *const filepath, t_cub *cub)
{
	//TODO insert brief
	cub->filepath = ft_strip(ft_strdup(filepath));
	if (!ft_is_ext(cub->filepath, ".cub"))
		ft_handle_error("Map: File extension", cub);
	cub->fd = open(cub->filepath, O_RDONLY);
	if (cub->fd == -1)
		ft_handle_error(NULL, cub);
	ft_init_map(cub->fd, cub);
	close(cub->fd);
	cub->fd = -1;
}
