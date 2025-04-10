#include "../includes/cub3d_bonus.h"

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
	if (map->door)
		free(map->door);
	if (map->sprite)
		free(map->sprite);
}

/**
 * @brief Cleans up and destroys all HUD-related images to free resources.
 *
 * This function destroys all the images related to the HUD, such as the 
 * watch, viewmodels, bread, and breadcrumbs, by calling `mlx_destroy_image`. 
 * It ensures that all image resources are properly freed when the HUD is no 
 * longer needed, preventing memory leaks.
 *
 * @param cub The main game structure containing the HUD and image data.
 */
void	ft_clean_hud(t_cub *cub)
{
	if (cub->hud->watch.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->watch.img_ptr);
	if (cub->hud->viewmodel_0.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_0.img_ptr);
	if (cub->hud->viewmodel_1.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_1.img_ptr);
	if (cub->hud->viewmodel_2.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_2.img_ptr);
	if (cub->hud->viewmodel_3.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_3.img_ptr);
	if (cub->hud->viewmodel_4.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel_4.img_ptr);
	if (cub->hud->bread.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->bread.img_ptr);
	if (cub->hud->empty_bread.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->empty_bread.img_ptr);
	if (cub->hud->breadcrumbs.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->breadcrumbs.img_ptr);
	free(cub->hud);
}

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
 * @brief Frees all images associated with the raycasting engine.
 *
 * Destroys all loaded wall and sprite textures using `mlx_destroy_image`.
 * This function ensures that memory associated with MLX image buffers is
 * properly released before freeing the `raycast` structure itself.
 *
 * @param cub Pointer to the main game structure containing the MLX instance and
 *        raycast data.
 */
static void	ft_clean_raycast(t_cub *cub)
{
	if (cub->raycast->north_texture.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->north_texture.img_ptr);
	if (cub->raycast->south_texture.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->south_texture.img_ptr);
	if (cub->raycast->east_texture.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->east_texture.img_ptr);
	if (cub->raycast->west_texture.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->west_texture.img_ptr);
	if (cub->raycast->sprite_still.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->sprite_still.img_ptr);
	if (cub->raycast->sprite_move.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->sprite_move.img_ptr);
	if (cub->raycast->sprite_eat.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->sprite_eat.img_ptr);
	if (cub->raycast->door_closed.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->door_closed.img_ptr);
	if (cub->raycast->door_open.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->door_open.img_ptr);
	if (cub->raycast->grab_go.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->grab_go.img_ptr);
	if (cub->raycast->grab_go2.img_ptr)
		mlx_destroy_image(cub->mlx, cub->raycast->grab_go2.img_ptr);
	int i = 0; //fix later
	while (i < 12)
	{
		if (cub->raycast->doors[i].img_ptr)
			mlx_destroy_image(cub->mlx, cub->raycast->doors[i].img_ptr);
		i++;
	}
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
			close(cub->fd); //not sure if it's necessary
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
		if (cub->hud)
			ft_clean_hud(cub);
		ft_clean_screens(cub);
		if (cub->raycast)
		{
			ft_clean_raycast(cub);
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
