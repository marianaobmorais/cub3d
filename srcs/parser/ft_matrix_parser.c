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
 * This function assigns the player's position (x, y) and direction based on 
 * the character representing the player ('S', 'N', 'E', 'W'). It ensures that 
 * the player is assigned only once on the map. If a player has already been 
 * assigned, the function returns false, indicating an error. If the player 
 * is successfully assigned, it updates the player's position and direction.
 * 
 * @param c The character representing the player ('S', 'N', 'E', 'W').
 * @param game A pointer to the game structure (t_game) containing the map data.
 * @param x The x-coordinate of the player's position.
 * @param y The y-coordinate of the player's position.
 * @return true if the player's position and direction are successfully set, 
 *         false if the player has already been set.
 */
static bool	ft_set_player(char c, t_cub *cub, int x, int y)
{
	//update brief
	if (cub->map->player_squ_x == -1)
	{
		cub->map->player_squ_x = x;
		cub->map->player_squ_y = y;
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
 * @brief Checks a line of the map for validity and assigns player position.
 * 
 * Validates each character in the given line, ensuring that it is one of the 
 * acceptable characters for the map ('1', '0', ' ', 'S', 'N', 'E', 'W'). If any 
 * invalid character is found, the function returns false. If the line contains 
 * a player character ('S', 'N', 'E', 'W'), it calls `ft_set_player` to assign 
 * the player's position and direction. The function returns true if the line 
 * is valid and the player is properly set.
 * 
 * @param line The map line to check.
 * @param x The x-coordinate of the line's position.
 * @param game A pointer to the game structure (t_game) to store the player's data.
 * @return true if the line is valid and the player is set, false otherwise.
 */
static bool	ft_check_line(char *line, int y, t_cub *cub)
{
	//update brief
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
 * @brief Parses the map matrix and validates each line.
 * 
 * Iterates through each line in the map matrix, stripping extra spaces and 
 * checking for valid characters using `ft_check_line`. The function also 
 * validates that the walls of the map are correctly defined using 
 * `ft_valid_wall`. 
 * If any line is invalid or if the player's position is not set, it triggers 
 * an error using `ft_handle_error`. The function ensures that the map structure 
 * adheres to the expected format.
 * 
 * @param game A pointer to the game structure (t_game) containing the map data.
 * @param matrix A 2D array representing the map's matrix.
 */
void	ft_matrix_parser(t_cub *cub, char **matrix)
{
	//update brief
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
		printf("%s\n", line);
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
