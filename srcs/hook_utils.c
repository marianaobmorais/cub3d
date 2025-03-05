#include "../includes/cub3d.h"

int	ft_close_window(t_cub *cub)
{
	ft_clean_game(cub);
	exit(0);
}

void	ft_player_motion(int y, int x, t_cub *cub)
{
	int	old_x;
	int	old_y;

	old_x = cub->map->player_pos_x;
	old_y = cub->map->player_pos_y;
	if (cub->map->matrix[y][x] == '1')
		return ;
	cub->map->player_pos_x = x;
	cub->map->player_pos_y = y;
	cub->map->matrix[old_y][old_x] = '0';
	cub->map->matrix[y][x] = 'S';
	ft_print_map(cub->map); //debug
	ft_put_minimap(cub); //debug
}

void run_game(t_cub *cub)
{
	//change
	ft_init_minimap(cub); //bonus
	ft_put_image(cub);
	ft_put_minimap(cub); //bonus
}

void	ft_manage_movements(int keysym, t_cub *cub)
{
	if (cub->started == true && (keysym == XK_A || keysym == XK_a))
		ft_player_motion(cub->map->player_pos_y, cub->map->player_pos_x -1, cub); //left
	if (cub->started == true && (keysym == XK_D || keysym == XK_d))
		ft_player_motion(cub->map->player_pos_y, cub->map->player_pos_x +1, cub); //right
	if (cub->started == true && (keysym == XK_W || keysym == XK_w))
		ft_player_motion(cub->map->player_pos_y -1, cub->map->player_pos_x, cub); //up
	if (cub->started == true && (keysym == XK_S || keysym == XK_s))
		ft_player_motion(cub->map->player_pos_y +1, cub->map->player_pos_x, cub); //down
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
		run_game(cub); //change
	}
}

int	ft_key_input(int keysym, t_cub *cub)
{
	if (cub->started == false && keysym == XK_Return)
	{
		cub->started = true;
		printf("press enter\n"); //debug
		run_game(cub); //change
	}
	if (cub->started == false && keysym == XK_Escape)
		ft_close_window(cub);
	if (cub->started == true && keysym == XK_Escape)
	{
		if (cub->leaving == true)
		{
			cub->leaving = false;
			run_game(cub); //change
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
