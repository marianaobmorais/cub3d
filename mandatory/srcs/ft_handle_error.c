/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:38:58 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/21 20:41:09 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Handles errors by printing an error message and cleaning up the game
 *        state.
 * 
 * This function prints an error message to the standard error output, cleans up
 * the resources used by the game (such as memory allocations), and then exits
 * the program with a status code of 1 to indicate failure. If no error message
 * is provided, a system error message is printed instead.
 * 
 * @param error_msg The error message to be printed (can be NULL for system
 *        error).
 * @param cub Pointer to the main game structure, used for cleanup.
 */
void	ft_handle_error(const char *error_msg, t_cub *cub)
{
	ft_fprintf(2, "Error\n");
	if (error_msg)
		ft_fprintf(2, "%s\n", error_msg);
	else
		perror("");
	ft_clean_game(cub);
	exit(1);
}
