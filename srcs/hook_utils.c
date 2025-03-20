#include "../includes/cub3d.h"

int	ft_close_window(t_cub *cub)
{
	ft_clean_game(cub);
	exit(0);
}

void	ft_rotate(t_cub *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->raycast->player_dir.x;
	cub->raycast->player_dir.x = cub->raycast->player_dir.x * cos(angle)
		- cub->raycast->player_dir.y * sin(angle);
	cub->raycast->player_dir.y = old_dir_x * sin(angle)
		+ cub->raycast->player_dir.y * cos(angle);
	old_plane_x = cub->raycast->camera_plane.x;
	cub->raycast->camera_plane.x = cub->raycast->camera_plane.x * cos(angle)
		- cub->raycast->camera_plane.y * sin(angle);
	cub->raycast->camera_plane.y = old_plane_x * sin(angle)
		+ cub->raycast->camera_plane.y * cos(angle);
}

void	ft_handle_img(t_cub *cub)
{
	ft_put_image(cub);
	ft_put_hud(cub);
}

void	ft_manage_movements(int keysym, t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = cub->raycast->player_pos.x;
	tmp_y = cub->raycast->player_pos.y;
	if (cub->started == true && (keysym == XK_A || keysym == XK_a))
		ft_move_left(cub, &tmp_x, &tmp_y);
	if (cub->started == true && (keysym == XK_D || keysym == XK_d))
		ft_move_right(cub, &tmp_x, &tmp_y);
	if (cub->started == true && (keysym == XK_W || keysym == XK_w))
		ft_move_up(cub, &tmp_x, &tmp_y);
	if (cub->started == true && (keysym == XK_S || keysym == XK_s))
		ft_move_down(cub, &tmp_x, &tmp_y);
	if (cub->map->matrix[(int)tmp_x][(int)tmp_y] != '1')
		ft_update_position(cub, tmp_x, tmp_y);
	if (keysym == XK_Left)
		ft_rotate(cub, MOVE_SPEED);
	if (keysym == XK_Right)
		ft_rotate(cub, -MOVE_SPEED);
	ft_put_image(cub);
}


void	ft_manage_exit(int keysym, t_cub *cub)
{
	static int	dir;

	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
	{
		dir = 1;
		ft_put_end_screen(cub, dir); //up
	}
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
	{
		dir = 0;
		ft_put_end_screen(cub, dir); //down
	}
	if (keysym == XK_Return && dir == 1)
		ft_close_window(cub);
	if (keysym == XK_Return && dir == 0)
	{
		cub->leaving = false;
		ft_handle_img(cub);
	}
}

int	ft_key_input(int keysym, t_cub *cub)
{
	if (cub->started == false && keysym == XK_Return)
	{
		cub->started = true;
		ft_handle_img(cub);
	}
	if (cub->started == false && keysym == XK_Escape)
		ft_close_window(cub);
	if (cub->started == true && keysym == XK_Escape)
	{
		if (cub->leaving == true)
		{
			cub->leaving = false;
			ft_handle_img(cub);
			return (0);
		}
		cub->leaving = true;
		ft_put_end_screen(cub, 0);
	}
	if (cub->started == true && cub->leaving == true)
		ft_manage_exit(keysym, cub);
	if (cub->started == true && cub->leaving == false)
		ft_manage_movements(keysym, cub);
	return (0);
}
