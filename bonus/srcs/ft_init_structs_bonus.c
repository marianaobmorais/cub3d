/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/05 18:29:23 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void	ft_init_xpm_image(t_cub *cub, t_image *img, char *path)
{
	ft_memset(img, 0, sizeof(t_image));
	(img)->img_ptr = mlx_xpm_file_to_image(cub->mlx, path, 
		&(img)->width, &(img)->height);
	if (!(img)->img_ptr)
		ft_handle_error("mlx_xpm_file_to_image", cub);
	(img)->addr = mlx_get_data_addr((img)->img_ptr, &(img)->bpp, \
		&(img)->line_len, &(img)->endian);
	if (!(img)->addr)
		ft_handle_error("mlx_get_data_addr", cub);
}

/* static  */void	ft_init_sprite(t_cub *cub)
{
	//add brief
	t_raycast	*ray;
	int			i;

	i = 0;
	ray = cub->raycast;
	ft_memset(&ray->sprite[i], 0, sizeof(t_image));
	ray->sprite[i].img_ptr = mlx_xpm_file_to_image(cub->mlx, "assets/textures/sprite_1.xpm", &ray->sprite[i].width, &ray->sprite[i].height);
	ray->sprite[i].addr = mlx_get_data_addr(ray->sprite[i].img_ptr, &ray->sprite[i].bpp, &ray->sprite[i].line_len, &ray->sprite[i].endian);
	if (!ray->sprite[i].img_ptr || !ray->sprite[i].addr)
		ft_handle_error("problem loading sprite", cub); //rephrase later
}

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
 * @brief Loads texture images for the walls and initializes texture data.
 *
 * This function loads texture images from XPM files and initializes the
 * corresponding texture structures. It also verifies that all images are 
 * loaded correctly before retrieving their memory addresses.
 *
 * @param cub Pointer to the main game structure containing texture data.
 */
static void	ft_init_wall_texture(t_cub *cub)
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
	//ft_print_map(cub->map); //debug
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_handle_error("malloc: cub->mlx", cub);
	ft_init_image(cub);
	ft_init_raycast(cub);
	ft_init_wall_texture(cub);
	ft_init_hud(cub);
	cub->started = false;
	cub->leaving = false;
	cub->action = false; //action
	cub->duration_action = 0; //action
	cub->amount_action = 0; //action
	ft_init_sprite(cub); //sprite
	ft_init_screens(cub);
	ft_init_doors(cub);
	int i = 0;
	printf("count door --> %d\n", cub->map->door_count);
	while (i < cub->map->door_count)
	{
		printf("id: %d --> x %d y %d\n", (cub->map->door[i]).id, (cub->map->door[i]).tile.x, (cub->map->door[i]).tile.y);
		printf("door tile id: %d --> x %d y %d\n", (cub->map->door[i]).id, (cub->map->door[i]).door_tile.x, (cub->map->door[i]).door_tile.y);
		i++;
	}
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		ft_handle_error("malloc: cub->window", cub);
	return (cub);
}
