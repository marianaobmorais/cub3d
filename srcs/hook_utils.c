#include "../includes/cub3d.h"

int	ft_close_window(t_cub *cub)
{
	ft_clean_game(cub);
	exit(0);
}

int	ft_key_input(int keysym, t_cub *cub)
{
	int	tmp_x = cub->raycast->player_pos.x;
	int	tmp_y = cub->raycast->player_pos.y;

	if (keysym == XK_Escape)
		ft_close_window(cub);
	if (keysym == XK_A || keysym == XK_a)
	{
		//left
		printf("pressed a\n");
	}
	if (keysym == XK_D || keysym == XK_d)
		; //right
	if (keysym == XK_W || keysym == XK_w)
	{
		printf("pressed w\n");//debug //up
		tmp_x += cub->raycast->player_dir.x * cub->raycast->move_speed;
		tmp_y += cub->raycast->player_dir.y * cub->raycast->move_speed;
		if (cub->map->matrix[(int)tmp_x][(int)tmp_y] == '0')
		{
			cub->raycast->player_pos.x += cub->raycast->player_dir.x * cub->raycast->move_speed;
			cub->raycast->player_pos.y += cub->raycast->player_dir.y * cub->raycast->move_speed;
		}
		printf("x = %lf, y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
		ft_put_image(cub);
		ft_put_minimap(cub);
	}
	if (keysym == XK_S || keysym == XK_s)
	{
		printf("pressed s\n");//debug //down
		tmp_x -= cub->raycast->player_dir.x * cub->raycast->move_speed;
		tmp_y -= cub->raycast->player_dir.y * cub->raycast->move_speed;
		if (cub->map->matrix[(int)tmp_x][(int)tmp_y] == '0')
		{
			cub->raycast->player_pos.x -= cub->raycast->player_dir.x * cub->raycast->move_speed;
			cub->raycast->player_pos.y -= cub->raycast->player_dir.y * cub->raycast->move_speed;
		}
		printf("x = %lf, y = %lf\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y); //debug
		ft_put_image(cub);
		ft_put_minimap(cub);
	}
	return (0);
}