#include "../../includes/cub3d.h"

static bool	is_valid_zero(char *line, int y)
{
	if ((y > 0 && (line[y - 1] == '0' || line[y - 1] == '1' ||
					line[y - 1] == 'S' || line[y - 1] == 'E' ||
					line[y - 1] == 'W' || line[y - 1] == 'N')) &&
		(line[y + 1] == '0' || line[y + 1] == '1' ||
		 line[y + 1] == 'S' || line[y + 1] == 'E' ||
		 line[y + 1] == 'W' || line[y + 1] == 'N'))
		return (true);
	return (false);
}

static bool	is_valid_space(char *line, int y)
{
	if ((y > 0 && (line[y - 1] == ' ' || line[y - 1] == '1')) &&
		(line[y + 1] == ' ' || line[y + 1] == '1'))
		return (true);
	return (false);
}

static bool	is_valid_line_edges(char *line)
{
	int	len;

	len = 0;
	while (line[len])
		len++;
	if (len == 0 || line[0] != '1' || line[len - 1] != '1')
		return (false);
	return (true);
}

bool	ft_valid_wall(char *line)
{
	int	y;

	if (!is_valid_line_edges(line))
		return (false);
	y = 0;
	while (line[y])
	{
		if (line[y] == '0')
		{
			if (y == 0 || line[y + 1] == '\0' || !is_valid_zero(line, y))
				return (false);
		}
		else if (line[y] == ' ')
		{
			if (y == 0 || line[y + 1] == '\0' || !is_valid_space(line, y))
				return (false);
		}
		y++;
	}
	return (true);
}
