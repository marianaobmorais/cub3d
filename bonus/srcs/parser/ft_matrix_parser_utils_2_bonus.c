/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_parser_utils_2_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:34 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/31 14:40:19 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

// bool	is_valid_door(char *line, char *previous_line, int y)
// {
// 	if (previous_line)
// 	{
// 		if (!previous_line[y] || previous_line[y] == ' ')
// 		{
// 			return (false);
// 		}
// 	}
// 	if ((y > 0 && (line[y - 1] == '0' || line[y - 1] == '1'
// 				|| line[y - 1] == 'S' || line[y - 1] == 'E'
// 				|| line[y - 1] == 'W' || line[y - 1] == 'N' || line[y - 1] == 'D'))
// 		&& (line[y + 1] == '0' || line[y + 1] == '1'
// 			|| line[y + 1] == 'S' || line[y + 1] == 'E'
// 			|| line[y + 1] == 'W' || line[y + 1] == 'N' || line[y + 1] == 'D'))
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

bool	is_valid_sprite(char *line, char *previous_line, int x)
{
	(void)previous_line;
	if (previous_line)
	{
		if (previous_line[x] && previous_line[x] == ' ')
		{
			return (false);
		}
	}
	if (x > 0 && line[x - 1] != ' ' && line[x + 1] != ' ' && line[x + 1] != '\0')
	{
		return (true);
	}
	return (false);
}

void	ft_set_sprite(t_cub *cub, int x, int y)
{
	(cub->map->sprites[cub->map->sprites_increment]).tile.x = y;
	(cub->map->sprites[cub->map->sprites_increment]).tile.y = x;
	(cub->map->sprites[cub->map->sprites_increment]).id = cub->map->sprites_increment;
	cub->map->sprites_increment++;
}

void	ft_count_sprites(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	printf("line -> %s\n", line);
	while (line[i])
	{
		if (line[i] == 'X')
			cub->map->sprite_count++;
		i++;
	}
}
