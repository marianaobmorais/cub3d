/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 15:33:08 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Loads an XPM image and initializes a t_image structure.
 *
 * Uses MiniLibX functions to load an XPM file from the specified path into
 * an image structure. It also retrieves the image's address for pixel access.
 * On failure, it triggers an error handler.
 *
 * @param cub Pointer to the main game structure, used for MLX context and error
 *        handling.
 * @param img Pointer to the t_image structure to initialize.
 * @param path Path to the XPM image file to load.
 */
void	ft_init_xpm_image(t_cub *cub, t_image *img, char *path)
{
	ft_memset(img, 0, sizeof(t_image));
	img->img_ptr = mlx_xpm_file_to_image(cub->mlx, path, \
		&img->width, &img->height);
	if (!img->img_ptr)
		ft_handle_error("mlx_xpm_file_to_image", cub);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, \
		&img->line_len, &img->endian);
	if (!img->addr)
		ft_handle_error("mlx_get_data_addr", cub);
}

/**
 * @brief Initializes sprite textures and positions.
 *
 * Loads XPM images for sprite animation states (still, move, eat) and assigns
 * the default texture (still) to all map sprites. Also initializes each
 * sprite's position by centering it within its tile coordinates.
 *
 * @param cub Pointer to the main game structure containing raycasting and map
 *        data.
 */
static void	ft_init_sprites(t_cub *cub)
{
	t_raycast	*ray;
	int			i;

	ray = cub->raycast;
	ft_init_xpm_image(cub, &ray->sprite_still, "assets/textures/sprite_a0.xpm");
	ft_init_xpm_image(cub, &ray->sprite_move, "assets/textures/sprite_a1.xpm");
	ft_init_xpm_image(cub, &ray->sprite_eat, "assets/textures/sprite_b0.xpm");
	i = 0;
	while (i < cub->map->sprite_count)
	{
		cub->map->sprite[i].img = cub->raycast->sprite_still;
		cub->map->sprite[i].pos.x = cub->map->sprite[i].tile.x + 0.5;
		cub->map->sprite[i].pos.y = cub->map->sprite[i].tile.y + 0.5;
		i++;
	}
}

/**
 * @brief Initializes wall textures from XPM files.
 *
 * Loads wall texture images (north, south, east, and west) using the provided
 * file paths from the map structure. Each texture is stored in the
 * corresponding raycast texture slot.
 *
 * @param cub Pointer to the main game structure containing map data and
 *        raycasting context.
 */
static void	ft_init_wall_texture(t_cub *cub)
{
	//update brief
	t_raycast	*ray;

	ray = cub->raycast;
	ft_init_xpm_image(cub, &ray->north_texture, cub->map->north_texture);
	ft_init_xpm_image(cub, &ray->south_texture, cub->map->south_texture);
	ft_init_xpm_image(cub, &ray->east_texture, cub->map->east_texture);
	ft_init_xpm_image(cub, &ray->west_texture, cub->map->west_texture);
	ft_init_xpm_image(cub, &cub->raycast->grab_go, "assets/textures/g_g.xpm");
	ft_init_xpm_image(cub, &cub->raycast->grab_go2, "assets/textures/g_g2.xpm");
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
	cub->image = (t_image *)malloc(sizeof(t_image)); //remove later?
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
	cub->image->width = WIDTH;
	cub->image->height = HEIGHT;
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
		ft_handle_error("malloc:cub", cub);
	ft_memset(cub, 0, sizeof(t_cub));
	ft_load_map(argv, cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_handle_error("malloc: cub->mlx", cub);
	ft_init_image(cub);
	ft_init_raycast(cub);
	ft_init_wall_texture(cub);
	ft_init_hud(cub);
	ft_init_screens(cub);
	ft_init_doors(cub);
	ft_init_sprites(cub);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		ft_handle_error("malloc: cub->window", cub);
	return (cub);
}
