#include "../includes/cub3d_bonus.h"

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

void	ft_check_sprite_action(t_cub *cub)
{
	//add brief
	int			i;
	t_ipoint	tile;
	t_sprite	*sprite;

	i = 0;
	tile = cub->raycast->player_tile;
	sprite = cub->map->sprite;
	while (i < cub->map->sprite_count)
	{
		if ((tile.x == sprite[i].tile.x && tile.y == sprite[i].tile.y)
		|| (tile.x + 1 == sprite[i].tile.x && tile.y + 1 == sprite[i].tile.y)
		|| (tile.x - 1 == sprite[i].tile.x && tile.y - 1 == sprite[i].tile.y)
		|| (tile.x + 1 == sprite[i].tile.x && tile.y == sprite[i].tile.y)
		|| (tile.x == sprite[i].tile.x && tile.y + 1 == sprite[i].tile.y)
		|| (tile.x - 1 == sprite[i].tile.x && tile.y == sprite[i].tile.y)
		|| (tile.x == sprite[i].tile.x && tile.y - 1 == sprite[i].tile.y))
			sprite[i].sprite_action = true;
		i++;
	}
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
	t_dpoint	tmp;

	if (keysym == XK_Left)
		ft_rotate(cub, cub->raycast->rotate_speed);
	if (keysym == XK_Right)
		ft_rotate(cub, -cub->raycast->rotate_speed);
	tmp = cub->raycast->player_pos;
	if ((keysym == XK_A || keysym == XK_a))
		ft_move_left(cub, &tmp.x, &tmp.y);
	if ((keysym == XK_D || keysym == XK_d))
		ft_move_right(cub, &tmp.x, &tmp.y);
	if ((keysym == XK_W || keysym == XK_w))
		ft_move_up(cub, &tmp.x, &tmp.y);
	if ((keysym == XK_S || keysym == XK_s))
		ft_move_down(cub, &tmp.x, &tmp.y);
	if ((keysym == XK_Control_R || keysym == XK_Control_L)
		&& cub->amount_action < BREAD_3 + 1)
	{
		cub->action = true;
		cub->amount_action++;
		ft_check_sprite_action(cub);
	}
	if (keysym == XK_space)
		ft_open_or_close_door(cub);
	ft_update_position(cub, tmp.x, tmp.y);
	if (keysym == XK_M || keysym == XK_m)
	{
		if (!cub->raycast->mouse_status)
			cub->raycast->mouse_status = true;
		else
			cub->raycast->mouse_status = false;
	}
}

/**
 * @brief Handles user input when the exit screen is active.
 *
 * Responds to key presses to select and confirm exit options. 
 * Arrow keys or W/S are used to toggle between options. Pressing Enter with
 * the selected option either closes the window or cancels the exit and redraws
 * the main screen.
 *
 * @param keysym The key symbol pressed by the user.
 * @param cub A pointer to the main game structure.
 */
static void	ft_manage_exit(int keysym, t_cub *cub)
{
	static int	dir;

	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
	{
		dir = 1;
		ft_put_end_screen(cub, dir);
	}
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
	{
		dir = 0;
		ft_put_end_screen(cub, dir);
	}
	if (keysym == XK_Return && dir == 1)
		ft_close_window(cub);
	if (keysym == XK_Return && dir == 0)
	{
		cub->leaving = false;
		ft_handle_img(cub);
	}
}

/**
 * @brief Handles all key inputs during game runtime and at startup.
 *
 * This function processes key events based on the current game state. It
 * starts the game on Enter, exits on Escape before starting, manages the exit
 * screen when Escape is pressed during gameplay, and routes movement or exit
 * handling accordingly.
 *
 * @param keysym The key symbol pressed by the user.
 * @param cub A pointer to the main game structure.
 * @return Always returns 0.
 */
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
