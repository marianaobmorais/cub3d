#include "../../includes/cub3d.h"

static void	ft_init_map(t_cub *cub)
{
	//TODO insert brief
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
	cub->map->player_pos_x = -1;
	cub->map->player_pos_y = -1;
	cub->map->direction = -1;
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
	ft_init_map(cub);
	ft_map_parser(cub->fd, cub);
	ft_matrix_parser(cub, cub->map->matrix);
	close(cub->fd);
	cub->fd = -1;
}
