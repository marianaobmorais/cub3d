/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:38:54 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/07 15:02:07 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = NULL;
	if (argc != 2)
		ft_handle_error(strerror(EINVAL), cub);
	cub = ft_init_structs(cub, argv[1]);
	mlx_loop_hook(cub->mlx, ft_render_screen, cub);
	mlx_mouse_move(cub->mlx, cub->window, WIDTH / 2, HEIGHT / 2);
	mlx_hook(cub->window, KeyPress, KeyPressMask, ft_key_input, cub);
	mlx_hook(cub->window, DestroyNotify, NoEventMask, ft_close_window, cub);
	mlx_loop(cub->mlx);
	ft_clean_game(cub);
	return (0);
}
