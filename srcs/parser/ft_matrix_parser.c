#include "../../includes/cub3d.h"

/**
 * @brief Checks if a character is valid in the map configuration.
 * 
 * Validates if the given character is one of the following: wall ('1'), 
 * empty space ('0'), empty space (' '), or one of the player or direction 
 * markers ('S', 'N', 'E', 'W'). If the character is not one of these, the 
 * function returns false, indicating that the character is invalid for the 
 * map configuration. Otherwise, it returns true.
 * 
 * @param c The character to validate.
 * @return true if the character is valid, false otherwise.
 */
static bool	ft_valid_char(char c)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'S' && c != 'N'
		&& c != 'E' && c != 'W')
		return (false);
	return (true);
}

/**
 * @brief Sets the player's position and direction on the map.
 * 
 * This function sets the player's position on the map by storing the
 * coordinates in the `player_squ_x` and `player_squ_y` variables. It also
 * determines the player's facing direction based on the character passed 
 * ('N', 'S', 'E', 'W'). The function ensures that the player is only 
 * placed once on the map.
 * 
 * @param c The character representing the player's direction ('N', 'S', 
 *          'E', or 'W').
 * @param cub The main structure holding map data.
 * @param x The x-coordinate (row) of the player on the map.
 * @param y The y-coordinate (column) of the player on the map.
 * @return true if the player's position and direction were successfully 
 *         set, false if the player was already placed on the map.
 */
static bool	ft_set_player(char c, t_cub *cub, int x, int y)
{
	if (cub->map->player_squ_x == -1)
	{
		cub->map->player_squ_x = y;
		cub->map->player_squ_y = x;
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

/**
 * @brief Checks if a line in the map is valid and sets the player's position.
 * 
 * This function iterates over each character in a map line and validates it 
 * by ensuring that each character is a valid map character. If a player 
 * character ('S', 'N', 'E', 'W') is found, the player's position is set 
 * using the `ft_set_player` function. If any invalid characters or 
 * multiple player characters are found, the function returns false.
 * 
 * @param line The map line to check, as a null-terminated string.
 * @param y The y-coordinate (row) of the current line on the map.
 * @param cub The main structure holding the map data.
 * @return true if the line is valid, false otherwise.
 */
static bool	ft_check_line(char *line, int y, t_cub *cub)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!ft_valid_char(line[x]))
		{
			return (false);
		}
		if (line[x] == 'S' || line[x] == 'N' || line[x] == 'E'
			|| line[x] == 'W')
		{
			if (!ft_set_player(line[x], cub, x, y))
				return (false);
		}
		x++;
	}
	return (true);
}

/**
 * @brief Checks if a string contains only numeric characters.
 * 
 * Verifies whether the given string consists exclusively of digits (0-9). 
 * The function iterates over each character in the string and checks if each 
 * one is a valid digit. If any non-digit character is found, the function 
 * returns false.
 * 
 * @param nbr The string to check, as a null-terminated char array.
 * @return 1 if the string is entirely numeric, 0 otherwise.
 */
int	ft_isnumeric(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Parses the map matrix and validates the map's structure.
 * 
 * This function iterates through each line of the map matrix, checking if 
 * the characters in each line are valid using `ft_check_line`. It also 
 * validates the wall structure and player position using `ft_valid_wall` 
 * and `ft_set_player`. If any issues are found, an error message is raised.
 * 
 * @param cub The main structure holding the map data.
 * @param matrix The map matrix to be parsed, represented as an array of strings.
 * @return void
 */
void	ft_matrix_parser(t_cub *cub, char **matrix)
{
	int		y;
	bool	first_or_last;
	char	*line;
	char	*previous_line;

	y = 0;
	previous_line = NULL;
	while (matrix[y])
	{
		first_or_last = false;
		if (y == 0 || y + 1 == cub->map->height)
			first_or_last = true;
		line = matrix[y];
		if (y > 0)
			previous_line = matrix[y - 1];
		if (!ft_check_line(line, y, cub))
			ft_handle_error(MSG_MAP, cub);
		if (!ft_valid_wall(line, previous_line, first_or_last))
			ft_handle_error(MSG_MAP, cub);
		y++;
	}
	if (cub->map->player_squ_x == -1)
		ft_handle_error(MSG_MAP, cub);
}
