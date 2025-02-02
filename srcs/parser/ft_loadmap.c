#include "../../includes/cub3d.h"

/**
 * @brief Initializes the map structure within the game configuration.
 * 
 * Allocates memory for the map structure (t_map) and sets all its fields to 
 * default values. If memory allocation fails, the function handles the error 
 * appropriately. This initialization ensures the map is ready for parsing and 
 * further processing.
 * 
 * @param cub A pointer to the game structure (t_cub) where the map structure 
 *            will be initialized.
 */
static void	ft_init_map(t_cub *cub)
{
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
}

/**
 * @brief Loads and processes a map file for a game configuration.
 * 
 * Reads and validates a map file specified by the given filepath, ensuring it 
 * has the correct file extension (".cub") and is accessible. The function 
 * initializes the map, parses its content, and processes the map matrix for 
 * further use in the game. If any error occurs during these steps, it handles 
 * the error appropriately.
 * 
 * @param filepath The path to the map file, as a null-terminated string.
 * @param cub A pointer to the game structure (t_cub) where map data and 
 *            configuration will be stored.
 */
void	ft_loadmap(char *const filepath, t_cub *cub)
{
	cub->filepath = ft_strip(ft_strdup(filepath));
	if (!ft_is_ext(cub->filepath, ".cub"))
		ft_handle_error("Map: File extension", cub);
	cub->fd = -1;
	cub->fd = open(cub->filepath, O_RDONLY);
	if (cub->fd == -1)
		ft_handle_error(NULL, cub);
	ft_init_map(cub);
	ft_map_parser(cub->fd, cub);
	ft_matrix_parser(cub, cub->map->matrix);
	close(cub->fd);
	cub->fd = -1;
}
