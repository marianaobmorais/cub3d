/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:47 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/22 18:55:48 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Initializes the map structure within the game configuration.
 * 
 * Allocates memory for the map structure (t_map) and sets all its fields to 
 * default values. If memory allocation fails, the function handles the error 
 * appropriately. This initialization ensures the map is ready for parsing and 
 * further processing.
 * 
 * @param game A pointer to the game structure (t_game) where the map structure 
 *            will be initialized.
 */
static void	ft_init_map(t_cub *cub)
{
	cub->map = (t_map *) malloc(sizeof(t_map));
	if (!cub->map)
		ft_handle_error("Malloc: t_map", cub);
	cub->map->matrix = NULL;
	cub->map->matrix_tmp = NULL;
	cub->map->north_texture = NULL;
	cub->map->south_texture = NULL;
	cub->map->west_texture = NULL;
	cub->map->east_texture = NULL;
	cub->map->floor_rgb = NULL;
	cub->map->ceiling_rgb = NULL;
	cub->map->player_squ_x = -1;
	cub->map->player_squ_y = -1;
	cub->map->direction = -1;
}

/**
 * @brief Loads and parses the map file for the game.
 *
 * This function initializes the file path, checks if the file extension is
 * correct (".cub"), and attempts to open the map file. It then initializes
 * the map structure, parses the map data, processes the map matrix, and
 * calculates the ceiling and floor colors in hexadecimal. Finally, it closes
 * the file.
 *
 * @param filepath The path to the map file.
 * @param cub The main structure containing the map and game-related data.
 */
void	ft_load_map(char *const filepath, t_cub *cub)
{
	int	i;

	i = 0;
	cub->fd = -1;
	cub->filepath = ft_strip(ft_strdup(filepath), 0);
	if (!ft_is_ext(cub->filepath, ".cub"))
		ft_handle_error("Map: File extension", cub);
	cub->fd = open(cub->filepath, O_RDONLY);
	if (cub->fd == -1)
		ft_handle_error(NULL, cub);
	ft_init_map(cub);
	ft_map_parser(cub->fd, cub, i);
	ft_matrix_parser(cub, cub->map->matrix);
	cub->map->ceiling_hex = ft_arraytohex(cub->map->ceiling_rgb);
	cub->map->floor_hex = ft_arraytohex(cub->map->floor_rgb);
	close(cub->fd);
	cub->fd = -1;
}
