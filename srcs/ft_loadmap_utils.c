#include "../includes/cub3D.h"

void	ft_add_texture(char *line, t_cub *cub, char *identifier, \
	t_directions direction)
{
	//TODO add brief
	char	**tmp;
	char	*filepath;

	tmp = ft_split(line, ' ');
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

void	ft_add_color(char *line, t_cub *cub, char *identifier, \
	t_directions direction)
{
	//TODO add brief
	char	**tmp;

	if (ft_strncmp(identifier, line, 1) == 0 && !ft_isalpha(line[1]))
	{
		tmp = ft_split(line + 1, ',');
		if (direction == FLOOR && !cub->map->floor_rgb)
		{
			printf("FLOOR [%s, %s, %s]\n", tmp[0], tmp[1], tmp[2]); //debug
			ft_free_vector(tmp);
		}
		else if (direction == CEILING && !cub->map->ceiling_rgb)
		{
			printf("CEILING [%s, %s, %s]\n", tmp[0], tmp[1], tmp[2]); //debug
			ft_free_vector(tmp);
		}
		else
		{
			free(line);
			ft_free_vector(tmp);
			ft_handle_error("Color: duplicate", cub);
		}
	}
}

void	ft_add_map(char *line, t_cub *cub)
{
	//TODO add brief
	(void)cub;
	printf("line->%s\n", line); //debug
}
