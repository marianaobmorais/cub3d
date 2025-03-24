#include "../includes/cub3d.h"

/**
 * @brief Closes the game window and exits the program.
 *
 * Cleans up allocated resources, calls the game cleanup function, and 
 * terminates the program with an exit status of 0.
 *
 * @param cub Pointer to the main game structure.
 * @return Always returns 0.
 */
int	ft_close_window(t_cub *cub)
{
	ft_clean_game(cub);
	exit(0);
}

/**
 * @brief Rotates the player's direction and camera plane.
 *
 * Applies a rotation matrix to the player's direction vector and camera plane 
 * based on the given angle, allowing the player to look left or right.
 *
 * @param cub Pointer to the main game structure.
 * @param angle The rotation angle in radians (positive for left, negative for
 *        right).
 */
static void	ft_rotate(t_cub *cub, double angle)
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

/**
 * @brief Handles player movement and rotation based on key input.
 *
 * Processes key inputs for movement (W, A, S, D) and rotation (Left, Right).
 * Updates the player's position if movement is allowed, ensuring the new 
 * position does not collide with walls.
 *
 * @param keysym The keycode representing the pressed key.
 * @param cub Pointer to the main game structure.
 */
static void	ft_manage_movements(int keysym, t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;

	if (keysym == XK_Left)
		ft_rotate(cub, cub->raycast->move_speed);
	if (keysym == XK_Right)
		ft_rotate(cub, -cub->raycast->move_speed);
	tmp_x = cub->raycast->player_pos.x;
	tmp_y = cub->raycast->player_pos.y;
	if ((keysym == XK_A || keysym == XK_a))
	ft_move_left(cub, &tmp_x, &tmp_y);
	if ((keysym == XK_D || keysym == XK_d))
	ft_move_right(cub, &tmp_x, &tmp_y);
	if ((keysym == XK_W || keysym == XK_w))
	ft_move_up(cub, &tmp_x, &tmp_y);
	if ((keysym == XK_S || keysym == XK_s))
	ft_move_down(cub, &tmp_x, &tmp_y);
	printf("tmp before: x: %lf, y: %lf, tile: %c\n", tmp_x, tmp_y, cub->map->matrix[(int)tmp_x][(int)tmp_y]); //debug
	printf("player before: x: %lf, y: %lf, tile: %c\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y, cub->map->matrix[(int)tmp_x][(int)tmp_y]); //debug
	if (cub->map->matrix[(int)tmp_x][(int)tmp_y] != '1')
		ft_update_position(cub, tmp_x, tmp_y);
	printf("tmp After: x: %lf, y: %lf, tile: %c\n", tmp_x, tmp_y, cub->map->matrix[(int)tmp_x][(int)tmp_y]); //debug
	printf("player after: x: %lf, y: %lf, tile: %c\n\n", cub->raycast->player_pos.x, cub->raycast->player_pos.y, cub->map->matrix[(int)cub->raycast->player_pos.x][(int)cub->raycast->player_pos.y]); //debug
	//ft_handle_img(cub);
}

int	ft_key_input(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		ft_close_window(cub);
	ft_manage_movements(keysym, cub);
	return (0);
}
