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
 * Releases all resources associated with the game structure (t_cub), including 
 * closing the file descriptor, freeing the map structure and its contents, and 
 * deallocating other dynamically allocated fields. Ensures proper cleanup to 
 * prevent memory leaks.
 * 
 * @param cub A pointer to the game structure (t_cub) to be cleaned up. 
 *            The structure itself is also freed.
 */
void	ft_clean_cub(t_cub *cub)
{
	//update brief
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
		if (cub->ceiling)
		{
			if (cub->ceiling->img_ptr)
				mlx_destroy_image(cub->mlx, cub->ceiling->img_ptr);
			free(cub->ceiling);
		}
		if (cub->floor)
		{
			if (cub->floor->img_ptr)
				mlx_destroy_image(cub->mlx, cub->floor->img_ptr);
			free(cub->floor);
		}
		if (cub->window)
			mlx_destroy_window(cub->mlx, cub->window);
		if (cub->mlx)
		{
			mlx_destroy_display(cub->mlx);
			free(cub->mlx);
		}
	}
	free(cub);
}

/**
 * @brief Handles errors, logs a message, cleans resources, and exits the
 *        program.
 * 
 * Logs the provided error message or a system error message if no specific 
 * message is given. Cleans up all allocated resources within the game 
 * structure (t_cub) and terminates the program. The exit code and output 
 * destination for the error message should be specified during implementation.
 * 
 * @param error_msg The custom error message to display, or NULL to display 
 *                  a system error message.
 * @param cub A pointer to the game structure (t_cub) to clean up before 
 *            program termination.
 */
void	ft_handle_error(const char *error_msg, t_cub *cub)
{
	//update brief
	printf("Error\n"); //TODO stderr
	if (error_msg)
		printf("%s\n", error_msg); //TODO stderr
	else
		perror("");
	ft_clean_cub(cub);
	exit (1); // shouldn't exit with 0
}
