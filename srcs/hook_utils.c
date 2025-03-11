#include "../includes/cub3d.h"

int	ft_close_window(t_cub *cub)
{
	ft_clean_game(cub);
	exit(0);
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

int	ft_key_input(int keysym, t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = cub->raycast->player_pos.x;
	tmp_y = cub->raycast->player_pos.y;
	if (keysym == XK_Escape)
		ft_close_window(cub);
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
	if (keysym == XK_Left || keysym == XK_Right|| keysym == XK_A || keysym == XK_a || keysym == XK_D || keysym == XK_d || keysym == XK_W || keysym == XK_w || keysym == XK_S || keysym == XK_s)
	{
		//printf("print image\n\n");//debug
		ft_put_image(cub);
		//ft_put_minimap(cub);
	}
	return (0);
}


// int	ft_key_input(int keysym, t_cub *cub)
// {
// 	int			tmp_pos_x;
// 	int			tmp_pos_y;
// 	t_raycast	*ray;

// 	ray = cub->raycast;
// 	tmp_pos_x = ray->player_pos.x;
// 	tmp_pos_y = ray->player_pos.y;
// 	if (keysym == XK_Escape)
// 		ft_close_window(cub);
// 	if (keysym == XK_A || keysym == XK_a)
// 	{
// 		//left
// 		printf("pressed a\n");
// 		tmp_pos_x -= ray->camera_plane.x * ray->move_speed;
// 		tmp_pos_y -= ray->camera_plane.y * ray->move_speed;
// 		if (cub->map->matrix[(int)tmp_pos_x][(int)tmp_pos_y] == '0')
// 		{
// 			ray->player_pos.x = tmp_pos_x;
// 			ray->player_pos.y = tmp_pos_y;
// 		}
// 		printf("x = %lf, y = %lf\n", ray->player_pos.x, ray->player_pos.y); //debug
// 	}
// 	if (keysym == XK_D || keysym == XK_d)
// 	{
// 		//right
// 		printf("pressed d\n");
// 		tmp_pos_x += ray->camera_plane.x * ray->move_speed;
// 		tmp_pos_y += ray->camera_plane.y * ray->move_speed;
// 		if (cub->map->matrix[(int)tmp_pos_x][(int)tmp_pos_y] == '0') //sometimes it show beyond the wall
// 		{
// 			ray->player_pos.x = tmp_pos_x;
// 			ray->player_pos.y = tmp_pos_y;
// 		}
// 		printf("x = %lf, y = %lf\n", ray->player_pos.x, ray->player_pos.y); //debug
// 	}
// 	if (keysym == XK_W || keysym == XK_w)
// 	{
// 		//up
// 		printf("pressed w\n");//debug
// 		tmp_pos_x += ray->player_dir.x * ray->move_speed;
// 		tmp_pos_y += ray->player_dir.y * ray->move_speed;
// 		if (cub->map->matrix[(int)tmp_pos_x][(int)tmp_pos_y] == '0')
// 		{
// 			ray->player_pos.x = tmp_pos_x;
// 			ray->player_pos.y = tmp_pos_y;
// 		}
// 		printf("x = %lf, y = %lf\n", ray->player_pos.x, ray->player_pos.y); //debug
// 	}
// 	if (keysym == XK_S || keysym == XK_s)
// 	{
// 		//down
// 		printf("pressed s\n");//debug
// 		tmp_pos_x -= ray->player_dir.x * ray->move_speed;
// 		tmp_pos_y -= cub->raycast->player_dir.y * cub->raycast->move_speed;
// 		if (cub->map->matrix[(int)tmp_pos_x][(int)tmp_pos_y] == '0')
// 		{
// 			cub->raycast->player_pos.x = tmp_pos_x;
// 			cub->raycast->player_pos.y = tmp_pos_y;
// 		}
// 		printf("x = %lf, y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
// 	}

// 	// double	tmp_dir_x;
// 	// double	tmp_dir_y;
// 	// double	tmp_plane_x;
// 	// double	tmp_plane_y;

// 	// tmp_dir_x = ray->ray_dir.x;
// 	// tmp_dir_y = ray->ray_dir.y;
// 	// tmp_plane_x = ray->camera_plane.x;
// 	// tmp_plane_y = ray->camera_plane.y;
// 	// if (keysym == XK_Left)
// 	// {
// 	// 	//rotate left
// 	// 	/* ray->ray_dir.x */ = ;
// 	// }
// 	// if (keysym == XK_Right)
// 	// {
// 	// 	//rotate right
// 	// 	;
// 	// }
// 	// if (keysym == XK_A || keysym == XK_a || keysym == XK_D || keysym == XK_d
// 	// 	|| keysym == XK_W || keysym == XK_w || keysym == XK_S || keysym == XK_s
// 	// 	|| keysym == XK_Left || keysym == XK_Right)
// 	// {
// 		printf("print image\n"); //debug
// 		ft_put_image(cub);
// 		ft_put_minimap(cub);
// 	//}
// 	return (0);
// }