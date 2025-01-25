#include "../includes/cub3D.h"

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
