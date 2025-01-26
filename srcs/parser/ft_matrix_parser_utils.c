#include "../../includes/cub3d.h"

/**
 * @brief Validates the placement of a '0' character in a map wall line.
 * 
 * Ensures that a '0' character is surrounded by valid wall characters ('1') 
 * or valid player or enemy characters ('S', 'E', 'W', 'N'). This function 
 * checks the immediate neighbors of the '0' to verify its correct placement 
 * within the map structure.
 * 
 * @param line The map wall line to check, as a null-terminated string.
 * @param y The index of the '0' character in the line.
 * @return true if the '0' character is correctly placed, false otherwise.
 */
static bool	is_valid_zero(char *line, int y)
{
	if ((y > 0 && (line[y - 1] == '0' || line[y - 1] == '1'
		|| line[y - 1] == 'S' || line[y - 1] == 'E'
		|| line[y - 1] == 'W' || line[y - 1] == 'N'))
		&& (line[y + 1] == '0' || line[y + 1] == '1'
		|| line[y + 1] == 'S' || line[y + 1] == 'E'
		|| line[y + 1] == 'W' || line[y + 1] == 'N'))
		return (true);
	return (false);
}

/**
 * @brief Validates the placement of a space character in a map wall line.
 * 
 * Ensures that a space (' ') character is correctly placed between walls ('1')
 * or other spaces. The function checks the immediate neighbors of the space 
 * to ensure it is surrounded by valid characters.
 * 
 * @param line The map wall line to check, as a null-terminated string.
 * @param y The index of the space character in the line.
 * @return true if the space character is correctly placed, false otherwise.
 */
static bool	is_valid_space(char *line, int y)
{
	if ((y > 0 && (line[y - 1] == ' ' || line[y - 1] == '1'))
		&& (line[y + 1] == ' ' || line[y + 1] == '1'))
		return (true);
	return (false);
}

/**
 * @brief Validates the edges of a map wall line.
 * 
 * Checks whether the first and last characters of the line are walls ('1'). 
 * The function ensures that the line is non-empty and that the edges are 
 * correctly marked, as required by the map's structural rules.
 * 
 * @param line The map wall line to check, as a null-terminated string.
 * @return true if the edges are valid (first and last characters are '1'), 
 *         false otherwise.
 */
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

/**
 * @brief Validates a map wall line for proper structure and characters.
 * 
 * Checks whether a given line of a map wall is valid. It ensures that the 
 * edges of the line meet specific requirements, and verifies that '0' and 
 * ' ' characters are placed correctly according to predefined rules. The 
 * validation ensures the line adheres to the expected wall format.
 * 
 * @param line The map wall line to validate, as a null-terminated string.
 * @return true if the line is valid, false otherwise.
 */
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

/**
 * @brief Checks if a given string is empty or consists only of whitespace.
 * 
 * Determines whether the input string is NULL, empty, or contains only 
 * whitespace characters. The function creates a stripped copy of the input 
 * string to perform the check, ensuring the original string remains unaltered.
 * 
 * @param line The string to check, as a null-terminated char array. 
 *             Can be NULL.
 * @return 1 if the string is NULL, empty, or consists only of whitespace, 
 *         0 otherwise.
 */
int	ft_isempty(char *line)
{
	char	*tmp;

	if (!line)
		return (1);
	tmp = ft_strip(ft_strdup(line));
	if (!tmp)
		return (1);
	if (tmp[0] == '\0')
		return (free(tmp), 1);
	return (free(tmp), 0);
}
