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

/**
 * @brief Cleans up and frees memory allocated for the map structure.
 * 
 * Frees all dynamically allocated fields within the map structure (t_map), 
 * including the matrix, textures, and RGB values for the floor and ceiling. 
 * This function ensures proper deallocation to prevent memory leaks.
 * 
 * @param map A pointer to the map structure (t_map) to be cleaned up. 
 *            The structure itself is not freed.
 */
void	ft_clean_map(t_map *map)
{
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

/**
 * @brief Cleans up and frees memory allocated for the game structure.
 * 
 * Releases all resources associated with the game structure (t_game), including 
 * closing the file descriptor, freeing the map structure and its contents, and 
 * deallocating other dynamically allocated fields. Ensures proper cleanup to 
 * prevent memory leaks.
 * 
 * @param game A pointer to the game structure (t_game) to be cleaned up. 
 *            The structure itself is also freed.
 */
void	ft_clean_game(t_game *game)
{
	if (game)
	{
		if (game->fd != -1)
			close(game->fd);
		if (game->filepath)
			free(game->filepath);
		if (game->map)
		{
			ft_clean_map(game->map);
			free(game->map);
		}
		if (game->img)
		{
			if (game->img->img_ptr)
				mlx_destroy_image(game->mlx, game->img->img_ptr);
			free(game->img);
		}
		if (game->window)
				mlx_destroy_window(game->mlx, game->window);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
	free(game);
}

/**
 * @brief Handles errors, logs a message, cleans resources, and exits the
 *        program.
 * 
 * Logs the provided error message or a system error message if no specific 
 * message is given. Cleans up all allocated resources within the game 
 * structure (t_game) and terminates the program. The exit code and output 
 * destination for the error message should be specified during implementation.
 * 
 * @param error_msg The custom error message to display, or NULL to display 
 *                  a system error message.
 * @param game A pointer to the game structure (t_game) to clean up before 
 *            program termination.
 */
void	ft_handle_error(const char *error_msg, t_game *game)
{
	printf("Error\n"); //TODO stdout or stderr ?
	if (error_msg)
		printf("%s\n", error_msg);
	else
		perror("");
	ft_clean_game(game);
	exit (0);
}
