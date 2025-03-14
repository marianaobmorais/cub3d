#include "../includes/cub3d.h"

int	ft_close_window(t_cub *cub)
{
	ft_clean_game(cub);
	exit(0);
}

void	ft_handle_img(t_cub *cub)
{
	ft_put_image(cub);
	ft_put_hud(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->image->img_ptr, 0, 0);
}

void	test(t_cub *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->raycast->player_dir.x;
	cub->raycast->player_dir.x = cub->raycast->player_dir.x * cos(angle) - cub->raycast->player_dir.y * sin(angle);
	cub->raycast->player_dir.y = old_dir_x * sin(angle) + cub->raycast->player_dir.y * cos(angle);
	old_plane_x = cub->raycast->camera_plane.x; 
	cub->raycast->camera_plane.x = cub->raycast->camera_plane.x * cos(angle) - cub->raycast->camera_plane.y * sin(angle);
	cub->raycast->camera_plane.y = old_plane_x * sin(angle) + cub->raycast->camera_plane.y * cos(angle);
}

void	ft_player_motion(int y, int x, t_cub *cub)
{
	int	old_x;
	int	old_y;

	old_x = cub->map->player_squ_x;
	old_y = cub->map->player_squ_y;
	if (cub->map->matrix[y][x] == '1')
		return ;
	cub->map->player_squ_x = x;
	cub->map->player_squ_y = y;
	cub->map->matrix[old_y][old_x] = '0';
	cub->map->matrix[y][x] = 'S';
}

void	ft_manage_movements(int keysym, t_cub *cub)
{
	// if (cub->started == true && (keysym == XK_A || keysym == XK_a))
	// 	ft_player_motion(cub->map->player_squ_y, cub->map->player_squ_x -1, cub); //left
	// if (cub->started == true && (keysym == XK_D || keysym == XK_d))
	// 	ft_player_motion(cub->map->player_squ_y, cub->map->player_squ_x +1, cub); //right
	// if (cub->started == true && (keysym == XK_W || keysym == XK_w))
	// 	ft_player_motion(cub->map->player_squ_y -1, cub->map->player_squ_x, cub); //up
	// if (cub->started == true && (keysym == XK_S || keysym == XK_s))
	// 	ft_player_motion(cub->map->player_squ_y +1, cub->map->player_squ_x, cub); //down

	double	tmp_x;
	double	tmp_y;

	tmp_x = cub->raycast->player_pos.x;
	tmp_y = cub->raycast->player_pos.y;

	if (keysym == XK_A || keysym == XK_a)
	{
		//left
		//printf("pressed a\n"); //debug
		tmp_x -= cub->raycast->camera_plane.x * cub->raycast->move_speed;
		tmp_y -= cub->raycast->camera_plane.y * cub->raycast->move_speed;
		//printf("tmp_x = %lf, tmp_y = %lf\n", tmp_x, tmp_y); //debug
		//printf("cub->map->matrix[(int)tmp_x][(int)tmp_y] = %c\n", cub->map->matrix[(int)tmp_x][(int)tmp_y]); //debug
		if (cub->map->matrix[(int)tmp_x][(int)tmp_y] != '1')
		{
			cub->raycast->player_pos.x = tmp_x;
			cub->raycast->player_pos.y = tmp_y;
			cub->raycast->player_squ.x = floor(tmp_x);
			cub->raycast->player_squ.y =  floor(tmp_y);
		}
		//printf("player_pos_x = %lf, player_pos_y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
	}
	if (keysym == XK_D || keysym == XK_d)
	{
		//right
		//printf("pressed d\n");//debug
		tmp_x += cub->raycast->camera_plane.x * cub->raycast->move_speed;
		tmp_y += cub->raycast->camera_plane.y * cub->raycast->move_speed;
		//printf("tmp_x = %lf, tmp_y = %lf\n", tmp_x, tmp_y); //debug
		//printf("cub->map->matrix[(int)tmp_x][(int)tmp_y] = %c\n", cub->map->matrix[(int)tmp_x][(int)tmp_y]); //debug
		if (cub->map->matrix[(int)tmp_x][(int)tmp_y] != '1') //sometimes it show beyond the wall
		{
			cub->raycast->player_pos.x = tmp_x;
			cub->raycast->player_pos.y = tmp_y;
			cub->raycast->player_squ.x = floor(tmp_x);
			cub->raycast->player_squ.y =  floor(tmp_y);
		}
		//printf("player_pos_x = %lf, player_pos_y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
	}
	if (keysym == XK_W || keysym == XK_w)
	{
		//up
		//printf("pressed w\n");//debug
		tmp_x += cub->raycast->player_dir.x * cub->raycast->move_speed;
		tmp_y += cub->raycast->player_dir.y * cub->raycast->move_speed;
		//printf("tmp_x = %lf, tmp_y = %lf\n", tmp_x, tmp_y); //debug
		//printf("cub->map->matrix[(int)tmp_x][(int)tmp_y] = %c\n", cub->map->matrix[(int)tmp_x][(int)tmp_y]); //debug
		if (cub->map->matrix[(int)tmp_x][(int)tmp_y] != '1')
		{
			cub->raycast->player_pos.x = tmp_x;
			cub->raycast->player_pos.y = tmp_y;
			cub->raycast->player_squ.x = floor(tmp_x);
			cub->raycast->player_squ.y =  floor(tmp_y);
		}
		//printf("player_pos_x = %lf, player_pos_y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
	}
	if (keysym == XK_S || keysym == XK_s)
	{
		//down
		//printf("pressed s\n");//debug
		tmp_x -= cub->raycast->player_dir.x * cub->raycast->move_speed;
		tmp_y -= cub->raycast->player_dir.y * cub->raycast->move_speed;
		//printf("tmp_x = %lf, tmp_y = %lf\n", tmp_x, tmp_y); //debug
		//printf("cub->map->matrix[(int)tmp_x][(int)tmp_y] = %c\n", cub->map->matrix[(int)tmp_x][(int)tmp_y]); //debug
		if (cub->map->matrix[(int)tmp_x][(int)tmp_y] != '1')
		{
			cub->raycast->player_pos.x = tmp_x;
			cub->raycast->player_pos.y = tmp_y;
			cub->raycast->player_squ.x = floor(tmp_x);
			cub->raycast->player_squ.y =  floor(tmp_y);
		}
		//printf("player_pos_x = %lf, player_pos_y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
	}
	if (keysym == XK_Left)
	{
		test(cub, 0.1);
	}
	if (keysym == XK_Right)
	{
		test(cub, -0.1);
	}

	if (keysym == XK_space)
	{
		//printf("press space\n"); //debug
		ft_paint_action_on_hud(cub, cub->hud->breadcrumbs, 0, 0); //paint breadcrumbs image
		ft_handle_img(cub);
	}
	if (keysym == XK_Left || keysym == XK_Right || keysym == XK_A || keysym == XK_a || keysym == XK_D || keysym == XK_d || keysym == XK_W || keysym == XK_w || keysym == XK_S || keysym == XK_s)
	{
		//printf("print image\n");
		ft_handle_img(cub);
	}
	//printf("player_pos_x = %lf, player_pos_y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
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
