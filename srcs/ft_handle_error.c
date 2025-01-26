#include "../includes/cub3d.h"

/**
 * @brief Frees all strings in a vector (array of strings) and the vector
 *        itself.
 *
 * This function iterates through the array of strings (vector), freeing each
 * string individually. After all strings are freed, the function frees the
 * vector pointer itself to prevent memory leaks.
 *
 * @param vector A pointer to the array of strings to be freed.
 */
void	ft_free_vector(char **vector)
{
	int	i;

	i = 0;
	if (vector)
	{
		while (vector[i])
		{
			free(vector[i]);
			i++;
		}
		free(vector);
	}
}

void	ft_clean_map(t_map *map)
{
	//TODO add brief
	if (map->matrix)
		ft_free_vector(map->matrix);
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->west_texture)
		free(map->west_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->ceiling_rgb)
		free(map->ceiling_rgb);
	if (map->floor_rgb)
		free(map->floor_rgb);
}

void	ft_clean_cub(t_cub *cub)
{
	//TODO add brief
	if (cub)
	{
		if (cub->fd != -1)
			close(cub->fd);
		if (cub->filepath)
			free(cub->filepath);
		if (cub->map)
		{
			ft_clean_map(cub->map);
			free(cub->map);
		}
	}
	free(cub);
}

void	ft_handle_error(const char *error_msg, t_cub *cub)
{
	//TODO insert brief
	(void)cub;

	printf("Error\n"); //TODO stdout or stderr ?
	if (error_msg)
		printf("%s\n", error_msg);
	else
		perror("");
	ft_clean_cub(cub);
	exit (0); //TODO exit code
}
