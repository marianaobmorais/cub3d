#include "../includes/cub3d_bonus.h"

int	ft_mouse_hook(t_cub *cub)
{
	cub->raycast->mouse_time += cub->frame_time;
	if (cub->raycast->mouse_time >= 0.05)
	{
		mlx_mouse_get_pos(cub->mlx, cub->window, &cub->raycast->mouse_pos.x, &cub->raycast->mouse_pos.y);
		if ((cub->raycast->mouse_pos.x >= 0 && cub->raycast->mouse_pos.x < WIDTH / 2))
			ft_rotate(cub, cub->raycast->move_speed);
		if ((cub->raycast->mouse_pos.x > WIDTH / 2 && cub->raycast->mouse_pos.x < WIDTH))
			ft_rotate(cub, -cub->raycast->move_speed);
		cub->raycast->mouse_time = 0;
	}
	mlx_mouse_move(cub->mlx, cub->window, WIDTH / 2, HEIGHT / 2); //testing
	return (0);
}