#include "../includes/cub3d.h"

/**
 * @brief Handles errors, logs a message, cleans resources, and exits the
 *        program.
 * 
 * Logs the provided error message or a system error message if no specific 
 * message is given. Cleans up all allocated resources within the game 
 * structure (t_game) and terminates the program. The exit code and output 
 * destination for the error message should be specified during implementation.
 * 
 * @param error_msg The custom error message to display, or NULL to display 
 *                  a system error message.
 * @param game A pointer to the game structure (t_game) to clean up before 
 *            program termination.
 */
void	ft_handle_error(const char *error_msg, t_cub *cub)
{
	//update brief
	printf("Error\n"); //TODO stderr
	if (error_msg)
		printf("%s\n", error_msg); //TODO stderr
	else
		perror("");
	ft_clean_game(cub);
	exit(1); // shouldn't exit with 0
}
