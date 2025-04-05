/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:10 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/05 18:04:53 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"


void	ft_init_xpm_image(t_cub *cub, t_image *img, char *path)
{
	//add brief
	ft_memset(img, 0, sizeof(t_image));
	img->img_ptr = mlx_xpm_file_to_image(cub->mlx, path, 
		&img->width, &img->height);
	if (!img->img_ptr)
		ft_handle_error("mlx_xpm_file_to_image", cub);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, \
		&img->line_len, &img->endian);
	if (!img->addr)
		ft_handle_error("mlx_get_data_addr", cub);
}

/* static  */void	ft_init_sprite(t_cub *cub)
{
	//add brief
	t_raycast	*ray;
	int			i;

	ray = cub->raycast;
	i = 0;
	ft_init_xpm_image(cub, &ray->sprite_a[0], "assets/textures/pigeon_a1.xpm");
	ft_init_xpm_image(cub, &ray->sprite_b[0], "assets/textures/pigeon_b1.xpm");
	//cub->map->sprite[0].img = cub->raycast->sprite_a[0];
	//cub->map->sprite[0].img = cub->raycast->sprite_b[0];
	while (i < cub->map->sprite_count)
	{
		//add condition here if (i % 3 = 0), then if (i % 3 = 1), and so on
		//ft_init_xpm_image(cub, &ray->sprite_a[0], "assets/textures/pigeon_a1.xpm");
		//ft_init_xpm_image(cub, &ray->sprite_b[0], "assets/textures/pigeon_b1.xpm");
		cub->map->sprite[i].pos.x = cub->map->sprite[i].tile.x + 0.5;
		cub->map->sprite[i].pos.y = cub->map->sprite[i].tile.y + 0.5;
		cub->map->sprite[i].img = cub->raycast->sprite_a[0];
		//cub->map->sprite[i].img = cub->raycast->sprite_b[0];
		//printf("sprite[%d].pos: x = %lf, y = %lf\n", i, cub->map->sprite[i].pos.x, cub->map->sprite[i].pos.y); //debug
		i++;
	}
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
	//update brief
	t_raycast	*ray;

	ray = cub->raycast;
	ft_init_xpm_image(cub, &ray->north_texture, cub->map->north_texture);
	ft_init_xpm_image(cub, &ray->south_texture, cub->map->south_texture);
	ft_init_xpm_image(cub, &ray->east_texture, cub->map->east_texture);
	ft_init_xpm_image(cub, &ray->west_texture, cub->map->west_texture);
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
	cub->image->width = WIDTH; //explore this
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
	ft_print_map(cub->map); //debug
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_handle_error("malloc: cub->mlx", cub);
	ft_init_image(cub);
	ft_init_raycast(cub);
	ft_init_wall_texture(cub);
	ft_init_hud(cub);
	cub->action = false; //action
	cub->duration_action = 0; //action
	cub->amount_action = 0; //action
	ft_init_sprite(cub); //sprite
	ft_init_start_screen(cub);
	ft_init_end_screen(cub);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		ft_handle_error("malloc: cub->window", cub);
	return (cub);
}
