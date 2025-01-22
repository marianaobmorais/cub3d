#include "../includes/cub3D.h"

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

void	ft_add_map(char *line, t_cub *cub)
{
	//TODO add brief
	(void)cub;
	printf("line->%s\n", line); //debug
}
