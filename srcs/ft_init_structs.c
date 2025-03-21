/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/21 10:59:05 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Retrieves and stores texture memory addresses.
 *
 * This function initializes the memory addresses for the north, south, east, 
 * and west textures using `mlx_get_data_addr`. If any texture address retrieval
 * fails, it triggers an error handling function.
 *
 * @param cub Pointer to the main game structure containing raycasting data.
 */
static void	ft_get_img_addr(t_cub *cub)
{
	t_raycast	*ray;

	ray = cub->raycast;
	ray->north_texture.addr = mlx_get_data_addr(ray->north_texture.img_ptr,
			&ray->north_texture.bpp, &ray->north_texture.line_len,
			&ray->north_texture.endian);
	ray->south_texture.addr = mlx_get_data_addr(ray->south_texture.img_ptr,
			&ray->south_texture.bpp, &ray->south_texture.line_len,
			&ray->south_texture.endian);
	ray->east_texture.addr = mlx_get_data_addr(ray->east_texture.img_ptr,
			&ray->east_texture.bpp, &ray->east_texture.line_len,
			&ray->east_texture.endian);
	ray->west_texture.addr = mlx_get_data_addr(ray->west_texture.img_ptr,
			&ray->west_texture.bpp, &ray->west_texture.line_len,
			&ray->west_texture.endian);
	if (!ray->north_texture.addr || !ray->south_texture.addr
		|| !ray->east_texture.addr || !ray->west_texture.addr)
		ft_handle_error("texture.addr", cub);
}

/**
 * @brief Loads texture images and initializes texture data.
 *
 * This function loads texture images from XPM files and initializes the
 * corresponding texture structures. It also verifies that all images are 
 * loaded correctly before retrieving their memory addresses.
 *
 * @param cub Pointer to the main game structure containing texture data.
 */
static void	ft_init_texture(t_cub *cub)
{
	t_raycast	*ray;

	ray = cub->raycast;
	ft_memset(&ray->north_texture, 0, sizeof(t_image));
	ft_memset(&ray->south_texture, 0, sizeof(t_image));
	ft_memset(&ray->east_texture, 0, sizeof(t_image));
	ft_memset(&ray->west_texture, 0, sizeof(t_image));
	ray->north_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
			cub->map->north_texture, &ray->north_texture.width,
			&ray->north_texture.height);
	ray->south_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
			cub->map->south_texture, &ray->south_texture.width,
			&ray->south_texture.height);
	ray->east_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
			cub->map->east_texture, &ray->east_texture.width,
			&ray->east_texture.height);
	ray->west_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
			cub->map->west_texture, &ray->west_texture.width,
			&ray->west_texture.height);
	if (!ray->north_texture.img_ptr || !ray->south_texture.img_ptr
		|| !ray->east_texture.img_ptr || !ray->west_texture.img_ptr)
		ft_handle_error("texture.img_ptr", cub);
	ft_get_img_addr(cub);
}

/**
 * @brief Initializes the main image buffer for rendering.
 *
 * Allocates and initializes the image buffer used for rendering the game scene.
 * If memory allocation or image creation fails, an error is triggered.
 *
 * @param cub Pointer to the main game structure containing image data.
 */
static void	ft_init_image(t_cub *cub)
{
	cub->image = (t_image *)malloc(sizeof(t_image));
	if (!cub->image)
		ft_handle_error("malloc: cub->image", cub);
	ft_memset(cub->image, 0, sizeof(t_image));
	cub->image->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image->img_ptr)
		ft_handle_error("malloc: cub->image->img_ptr", cub);
	cub->image->addr = mlx_get_data_addr(cub->image->img_ptr, &cub->image->bpp,
			&cub->image->line_len, &cub->image->endian);
	if (!cub->image->addr)
		ft_handle_error("cub->image->addr", cub);
}

/**
 * @brief Initializes and allocates all core game structures.
 *
 * Allocates memory for the main game structure and its components, including
 * the map, raycasting system, textures, and graphical window. If any allocation
 * or initialization fails, an error is handled accordingly.
 *
 * @param cub Pointer to the main game structure.
 * @param argv The path to the map file.
 * @return A pointer to the initialized game structure.
 */
t_cub	*ft_init_structs(t_cub *cub, char *argv)
{
	cub = (t_cub *) malloc(sizeof(t_cub));
	if (!cub)
		ft_handle_error("malloc: cub", cub);
	ft_memset(cub, 0, sizeof(t_cub));
	ft_load_map(argv, cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_handle_error("malloc: cub->mlx", cub);
	ft_init_image(cub);
	ft_init_raycast(cub);
	ft_init_texture(cub);
	ft_init_hud(cub);
	ft_init_start_screen(cub); //screen
	ft_init_end_screen(cub); //screen
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		ft_handle_error("malloc: cub->window", cub);
	return (cub);
}
