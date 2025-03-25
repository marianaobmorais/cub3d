#include "../../includes/cub3d_bonus.h"

void	ft_init_start_screen(t_cub *cub)
{
	cub->start_screen = malloc(sizeof(t_screen));
	if (!cub->start_screen)
		ft_handle_error("malloc: cub->start_screen", cub);
	cub->started = false;
	cub->leaving = false;
	cub->start_screen->img = NULL;
	cub->start_screen->width = WIDTH;
	cub->start_screen->height = HEIGHT;
	cub->start_screen->paths = malloc(sizeof(char *) * 4);
	if (!cub->start_screen->paths)
		ft_handle_error("malloc: cub->start_screen->paths", cub);
	cub->start_screen->paths[0] = "assets/screens/start_screen0.xpm";
	cub->start_screen->paths[1] = "assets/screens/start_screen1.xpm";
	cub->start_screen->paths[2] = "assets/screens/start_screen2.xpm";
	cub->start_screen->paths[3] = "assets/screens/start_screen3.xpm";
}

void	ft_init_end_screen(t_cub *cub)
{
	cub->end_screen = malloc(sizeof(t_screen));
	if (!cub->end_screen)
		ft_handle_error("malloc: cub->end_screen", cub);
	cub->end_screen->img = NULL;
	cub->end_screen->width = WIDTH;
	cub->end_screen->height = HEIGHT;
	cub->end_screen->paths = malloc(sizeof(char *) * 2);
	if (!cub->end_screen->paths)
		ft_handle_error("malloc: cub->end_screen->paths", cub);
	cub->end_screen->paths[0] = "assets/screens/end_screen0.xpm";
	cub->end_screen->paths[1] = "assets/screens/end_screen1.xpm";
}

/**
 * @brief Displays the end screen based on the game's outcome.
 *
 * This function displays an end screen image based on the provided direction 
 * (`dir`). It first destroys the previous end screen image, then loads and 
 * displays the appropriate image from a predefined set of images (paths[0] or 
 * paths[1]). The `dir` parameter determines which image is chosen (e.g., 
 * success or failure screen).
 *
 * @param cub Pointer to the main game structure.
 * @param dir Integer indicating the direction (0 for one image, 1 for another).
 *
 * @return 0 upon completion.
 */
int	ft_put_end_screen(t_cub *cub, int dir)
{
	if (cub->end_screen->img)
		mlx_destroy_image(cub->mlx, cub->end_screen->img);
	if (dir == 0)
	{
		cub->end_screen->img = mlx_xpm_file_to_image(cub->mlx, \
			cub->end_screen->paths[0], &cub->end_screen->width, \
			&cub->end_screen->height);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->end_screen->img, \
			0, 0);
	}
	if (dir == 1)
	{
		cub->end_screen->img = mlx_xpm_file_to_image(cub->mlx, \
			cub->end_screen->paths[1], &cub->end_screen->width, \
			&cub->end_screen->height);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->end_screen->img, \
			0, 0);
	}
	return (0);
}

/**
 * @brief Displays the start screen of the game with changing images.
 *
 * This function controls the display of a start screen sequence by cycling 
 * through images at a regular interval (every 0.2 seconds). It updates the 
 * image shown on the screen and ensures smooth transitions between the 
 * images. Once all images have been displayed, the cycle restarts.
 *
 * @param cub Pointer to the main game structure.
 * @return 0 upon completion.
 */
int	ft_render_screen(t_cub *cub)
{
	clock_t		now;
	double		elapsed;

	now = clock();
	elapsed = (double)(now - cub->last_time) / CLOCKS_PER_SEC;
	if (!cub->started && elapsed >= 0.2)
	{
		if (cub->current_screen == 4)
			cub->current_screen = 0;
		if (cub->start_screen->img)
			mlx_destroy_image(cub->mlx, cub->start_screen->img);
		cub->start_screen->img = mlx_xpm_file_to_image(cub->mlx, \
			cub->start_screen->paths[cub->current_screen], \
			&cub->start_screen->width, \
			&cub->start_screen->height);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->start_screen->img, \
			0, 0);
		cub->last_time = now;
		cub->current_screen++;
	}
	if (cub->started && !cub->leaving && elapsed >= 0.016)
		ft_handle_img(cub);
	if (cub->started && cub->action)
	{
		
	}
	return (0);
}
