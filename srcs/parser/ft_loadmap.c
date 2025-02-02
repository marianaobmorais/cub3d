#include "../../includes/cub3d.h"

/**
 * @brief Initializes the map structure within the game configuration.
 * 
 * Allocates memory for the map structure (t_map) and sets all its fields to 
 * default values. If memory allocation fails, the function handles the error 
 * appropriately. This initialization ensures the map is ready for parsing and 
 * further processing.
 * 
 * @param game A pointer to the game structure (t_game) where the map structure 
 *            will be initialized.
 */
static void	ft_init_map(t_game *game)
{
	game->map = (t_map *) malloc(sizeof(t_map));
	if (!game->map)
		ft_handle_error("Malloc: t_map", game);
	game->map->matrix = NULL;
	game->map->north_texture = NULL;
	game->map->south_texture = NULL;
	game->map->west_texture = NULL;
	game->map->east_texture = NULL;
	game->map->floor_rgb = NULL;
	game->map->ceiling_rgb = NULL;
	game->map->player_pos_x = -1;
	game->map->player_pos_y = -1;
	game->map->direction = -1;
}

/**
 * @brief Loads and processes a map file for a game configuration.
 * 
 * Reads and validates a map file specified by the given filepath, ensuring it 
 * has the correct file extension (".game") and is accessible. The function 
 * initializes the map, parses its content, and processes the map matrix for 
 * further use in the game. If any error occurs during these steps, it handles 
 * the error appropriately.
 * 
 * @param filepath The path to the map file, as a null-terminated string.
 * @param game A pointer to the game structure (t_game) where map data and 
 *            configuration will be stored.
 */
void	ft_loadmap(char *const filepath, t_game *game)
{
	game->filepath = ft_strip(ft_strdup(filepath));
	if (!ft_is_ext(game->filepath, ".cub"))
		ft_handle_error("Map: File extension", game);
	game->fd = open(game->filepath, O_RDONLY);
	if (game->fd == -1)
		ft_handle_error(NULL, game);
	ft_init_map(game);
	ft_map_parser(game->fd, game);
	ft_matrix_parser(game, game->map->matrix);
	close(game->fd);
	game->fd = -1;
}
