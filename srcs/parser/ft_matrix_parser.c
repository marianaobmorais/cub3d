#include "../../includes/cub3d.h"

static bool	ft_valid_char(char c)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'S' && c != 'N'
		&& c != 'E' && c != 'W')
		return (false);
	return (true);
}

static bool	ft_set_player(char c, t_cub *cub, int x, int y)
{
	if (cub->map->player_pos_x == -1)
	{
		cub->map->player_pos_x = x;
		cub->map->player_pos_y = y;
		if (c == 'S')
			cub->map->direction = SOUTH;
		if (c == 'N')
			cub->map->direction = NORTH;
		if (c == 'E')
			cub->map->direction = EAST;
		if (c == 'W')
			cub->map->direction = WEST;
	}
	else
		return (false);
	return (true);
}

static bool	ft_check_line(char *line, int x, t_cub *cub)
{
	int	y;

	y = 0;
	while (line[y])
	{
		if (!ft_valid_char(line[y]))
		{
			printf("error -> [%s]\n", line); //debug
			return (false);
		}
		if (line[y] == 'S' || line[y] == 'N' || line[y] == 'E' || line[y] == 'W')
		{
			if (!ft_set_player(line[y], cub, x, y))
				return (false);
		}
		y++;
	}
	return (true);
}

void	ft_matrix_parser(t_cub *cub, char **matrix)
{
	int		x; // line
	char	*line;

	x = 0;
	while (matrix[x])
	{
		line = ft_strip(ft_strdup(matrix[x]));
		if (!ft_check_line(line, x, cub) || !ft_valid_wall(line))
		{
			free(line);
			ft_handle_error(MSG_MAP, cub);
		}
		free(line);
		x++;
	}
	if (cub->map->player_pos_x == -1)
		ft_handle_error(MSG_MAP, cub);
}
