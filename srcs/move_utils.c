#include "../includes/cub3d.h"

void	ft_move_left(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x -= cub->raycast->camera_plane.x * cub->raycast->move_speed;
	*tmp_y -= cub->raycast->camera_plane.y * cub->raycast->move_speed;
}

void	ft_move_right(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x += cub->raycast->camera_plane.x * cub->raycast->move_speed;
	*tmp_y += cub->raycast->camera_plane.y * cub->raycast->move_speed;
}

void	ft_move_up(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x += cub->raycast->player_dir.x * cub->raycast->move_speed;
	*tmp_y += cub->raycast->player_dir.y * cub->raycast->move_speed;
}

void	ft_move_down(t_cub *cub, double *tmp_x, double *tmp_y)
{
	*tmp_x -= cub->raycast->player_dir.x * cub->raycast->move_speed;
	*tmp_y -= cub->raycast->player_dir.y * cub->raycast->move_speed;
}

void	ft_update_position(t_cub *cub, double tmp_x, double tmp_y)
{
	cub->raycast->player_pos.x = tmp_x;
	cub->raycast->player_pos.y = tmp_y;
	cub->raycast->player_squ.x = (int)tmp_x;
	cub->raycast->player_squ.y = (int)tmp_y;
}
