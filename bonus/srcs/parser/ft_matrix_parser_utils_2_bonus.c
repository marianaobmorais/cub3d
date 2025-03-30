/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_parser_utils_2_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:34 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/28 22:18:32 by joneves-         ###   ########.fr       */
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

bool	is_valid_pigeon(char *line, char *previous_line, int y)
{
	if (previous_line)
	{
		if (previous_line[y] && (previous_line[y] != ' '
				&& previous_line[y] != '1'))
		{
			return (false);
		}
	}
	if ((y > 0 && (line[y - 1] == ' ' || line[y - 1] == '1'))
		&& (line[y + 1] == ' ' || line[y + 1] == '1' || line[y + 1] == '\0'))
	{
		return (true);
	}
	if (y == 0 && (line[y] == ' ' || line[y] == '1'))
	{
		return (true);
	}
	return (false);
}

bool	ft_set_pigeon(t_cub *cub, int x, int y)
{
	if (is_valid_pigeon())
	{
		(cub->map->sprites[cub->map->sprites_increment]).squ_pos.x = y;
		(cub->map->sprites[cub->map->sprites_increment]).squ_pos.y = x;
		cub->map->sprites_increment++;
		if (cub->map->sprites_increment > cub->map->amount_sprites)
			(cub->map->sprites[cub->map->sprites_increment]) = NULL;
	}
	else
		return (false);
	return (true);
}

void	ft_count_sprites(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'F')
			cub->map->amount_sprites++;
		i++;
	}
}