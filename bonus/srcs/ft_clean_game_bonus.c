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
			ft_clean_hud(cub);
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
