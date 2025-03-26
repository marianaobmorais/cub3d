#include "../includes/cub3d_bonus.h"

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
static void	ft_clean_map(t_map *map)
{
	if (map->matrix)
		ft_free_vector(map->matrix);
	if (map->matrix_tmp)
		ft_free_vector(map->matrix_tmp);
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
void	ft_clean_game(t_cub *cub)
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
		if (cub->image)
		{
			if (cub->image->img_ptr)
				mlx_destroy_image(cub->mlx, cub->image->img_ptr);
			free(cub->image);
		}
		if (cub->hud) //bonus
		{
			if (cub->hud->img->img_ptr)
				mlx_destroy_image(cub->mlx, cub->hud->img->img_ptr);
			free(cub->hud->img);
			if (cub->hud->watch->img_ptr)
				mlx_destroy_image(cub->mlx, cub->hud->watch->img_ptr);
			free(cub->hud->watch);
			if (cub->hud->viewmodel->img_ptr)
				mlx_destroy_image(cub->mlx, cub->hud->viewmodel->img_ptr);
			free(cub->hud->viewmodel);
			if (cub->hud->bread->img_ptr)
				mlx_destroy_image(cub->mlx, cub->hud->bread->img_ptr);
			free(cub->hud->bread);
			if (cub->hud->empty_bread->img_ptr)
				mlx_destroy_image(cub->mlx, cub->hud->empty_bread->img_ptr);
			free(cub->hud->empty_bread);
			if (cub->hud->breadcrumbs->img_ptr)
					mlx_destroy_image(cub->mlx, cub->hud->breadcrumbs->img_ptr);
			free(cub->hud->breadcrumbs);
			if (cub->hud->door->img_ptr)
				mlx_destroy_image(cub->mlx, cub->hud->door->img_ptr);
			free(cub->hud->door);
			free(cub->hud);
		}
		if (cub->start_screen) //bonus
		{
			if (cub->start_screen->img)
				mlx_destroy_image(cub->mlx, cub->start_screen->img);
			free(cub->start_screen->paths);
			free(cub->start_screen);
		}
		if (cub->end_screen) //bonus
		{
			free(cub->end_screen->paths);
			if (cub->end_screen->img)
				mlx_destroy_image(cub->mlx, cub->end_screen->img);
			free(cub->end_screen);
		}
		if (cub->raycast)
		{
			if (cub->raycast->north_texture.img_ptr)
				mlx_destroy_image(cub->mlx, cub->raycast->north_texture.img_ptr);
			if (cub->raycast->south_texture.img_ptr)
				mlx_destroy_image(cub->mlx, cub->raycast->south_texture.img_ptr);
			if (cub->raycast->east_texture.img_ptr)
				mlx_destroy_image(cub->mlx, cub->raycast->east_texture.img_ptr);
			if (cub->raycast->west_texture.img_ptr)
				mlx_destroy_image(cub->mlx, cub->raycast->west_texture.img_ptr);
			free(cub->raycast);
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
