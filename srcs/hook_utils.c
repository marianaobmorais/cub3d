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
}

int	ft_key_input(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		ft_close_window(cub);
	if (keysym == XK_A || keysym == XK_a)
		ft_player_motion(cub->map->player_pos_y, cub->map->player_pos_x -1, cub); //left
	if (keysym == XK_D || keysym == XK_d)
		ft_player_motion(cub->map->player_pos_y, cub->map->player_pos_x +1, cub); //right
	if (keysym == XK_W || keysym == XK_w)
		ft_player_motion(cub->map->player_pos_y -1, cub->map->player_pos_x, cub); //up
	if (keysym == XK_S || keysym == XK_s)
		ft_player_motion(cub->map->player_pos_y +1, cub->map->player_pos_x, cub); //down
	return (0);
}