/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:14:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/24 17:14:11 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 * @brief Frees allocated memory for the map structure.
 * 
 * This function deallocates all dynamically allocated memory associated 
 * with the map, including matrices, textures, and RGB color values.
 * It ensures proper cleanup to prevent memory leaks.
 * 
 * @param cub The main game structure containing the map.
 */
static void	ft_clean_map(t_cub *cub)
{
	if (cub->map->matrix)
		ft_free_vector(cub->map->matrix);
	if (cub->map->matrix_tmp)
		ft_free_vector(cub->map->matrix_tmp);
	if (cub->map->north_texture)
		free(cub->map->north_texture);
	if (cub->map->south_texture)
		free(cub->map->south_texture);
	if (cub->map->west_texture)
		free(cub->map->west_texture);
	if (cub->map->east_texture)
		free(cub->map->east_texture);
	if (cub->map->ceiling_rgb)
		free(cub->map->ceiling_rgb);
	if (cub->map->floor_rgb)
		free(cub->map->floor_rgb);
	free(cub->map);
}

/**
 * @brief Frees allocated memory for the raycasting structure.
 * 
 * This function destroys the textures used in raycasting and 
 * deallocates the raycasting structure itself.
 * 
 * @param cub The main game structure containing the raycasting data.
 */
static void	ft_free_raycast(t_cub *cub)
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

/**
 * @brief Frees allocated memory for the image structure.
 * 
 * This function deallocates the main image used for rendering and 
 * frees the memory allocated for the image structure.
 * 
 * @param cub The main game structure containing the image.
 */
static void	ft_free_image(t_cub *cub)
{
	if (cub->image->img_ptr)
		mlx_destroy_image(cub->mlx, cub->image->img_ptr);
	free(cub->image);
}

/**
 * @brief Frees all allocated memory and resources in the game structure.
 * 
 * This function safely deallocates memory and closes file descriptors, 
 * images, textures, and other dynamically allocated resources associated 
 * with the `cub` structure. It ensures proper cleanup before exiting the 
 * program to prevent memory leaks.
 * 
 * @param cub The main game structure to be cleaned.
 */
void	ft_clean_game(t_cub *cub)
{
	if (cub)
	{
		if (cub->fd != -1)
			close(cub->fd);
		if (cub->filepath)
			free(cub->filepath);
		if (cub->map)
			ft_clean_map(cub);
		if (cub->image)
			ft_free_image(cub);
		if (cub->raycast)
			ft_free_raycast(cub);
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
