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
 * @brief Frees all HUD-related images.
 *
 * Destroys images associated with the HUD (e.g., watch, viewmodel, bread, empty
 * bread, breadcrumbs) using `mlx_destroy_image`, releasing MLX resources before
 * the HUD is deallocated.
 *
 * @param cub Pointer to the main game structure containing the MLX instance and
 * HUD data.
 */
void	ft_clean_hud(t_cub *cub)
{
	if (cub->hud->watch.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->watch.img_ptr);
	if (cub->hud->viewmodel.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->viewmodel.img_ptr);
	if (cub->hud->bread.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->bread.img_ptr);
	if (cub->hud->empty_bread.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->empty_bread.img_ptr);
	if (cub->hud->breadcrumbs.img_ptr)
		mlx_destroy_image(cub->mlx, cub->hud->breadcrumbs.img_ptr);
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
		ft_clean_doors(cub);
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
