/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_game_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 18:07:52 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
 * @brief Frees door textures by destroying loaded images.
 *
 * Iterates over all door image pointers in the raycasting context 
 * and destroys each image using mlx_destroy_image if it is not NULL. 
 * This helps to prevent memory leaks by cleaning up resources 
 * associated with door textures before exiting or reloading assets.
 *
 * @param cub Pointer to the main game context containing raycasting 
 *            data and the MLX instance.
 */
void	ft_clean_doors(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 13)
	{
		if (cub->raycast->doors[i].img_ptr)
			mlx_destroy_image(cub->mlx, cub->raycast->doors[i].img_ptr);
		i++;
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
	ft_clean_doors(cub);
	free(cub->raycast);
}

/**
 * @brief Cleans up and frees memory allocated for the game structure.
 * 
 * Releases all resources associated with the game structure (t_cub), including 
 * closing the file descriptor, freeing the map structure and its contents, and 
 * deallocating other dynamically allocated fields. Ensures proper cleanup to 
 * prevent memory leaks.
 * 
 * @param game A pointer to the game structure (t_cub) to be cleaned up. 
 *        The structure itself is also freed.
 */
void	ft_clean_game(t_cub *cub)
{
	if (cub)
	{
		if (cub->map)
			ft_clean_map(cub, cub->map);
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
			ft_clean_raycast(cub);
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
