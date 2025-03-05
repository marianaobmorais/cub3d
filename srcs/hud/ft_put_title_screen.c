#include "../../includes/cub3d.h"

void	ft_init_title_screen(t_cub *cub)
{
	cub->started = false;
	cub->leaving = false;
	cub->exit = false;
	cub->t_screen->screen = NULL;
	cub->t_screen->width = WIDTH;
	cub->t_screen->height = HEIGHT;
	cub->t_screen->paths = malloc(sizeof(char *) * 4);
	if (!cub->t_screen->paths)
		ft_handle_error("malloc: cub->t_screen->paths", cub);
	cub->t_screen->paths[0] = "assets/textures/initial_frame_01.xpm";
	cub->t_screen->paths[1] = "assets/textures/initial_frame_02.xpm";
	cub->t_screen->paths[2] = "assets/textures/initial_frame_03.xpm";
	cub->t_screen->paths[3] = "assets/textures/initial_frame_04.xpm";
	cub->e_screen->screen = NULL;
	cub->e_screen->width = WIDTH;
	cub->e_screen->height = HEIGHT;
	cub->e_screen->paths = malloc(sizeof(char *) * 2);
	if (!cub->e_screen->paths)
		ft_handle_error("malloc: cub->e_screen->paths", cub);
	cub->e_screen->paths[0] = "assets/textures/end_screen0.xpm";
	cub->e_screen->paths[1] = "assets/textures/end_screen1.xpm";
}

int	ft_put_end_screen(t_cub *cub, int dir)
{
	if (cub->e_screen->screen)
		mlx_destroy_image(cub->mlx, cub->e_screen->screen);
	if (dir == 0)
	{
		cub->e_screen->screen = mlx_xpm_file_to_image(cub->mlx, \
			cub->e_screen->paths[0], &cub->e_screen->width, \
			&cub->e_screen->height);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->e_screen->screen, \
			0, 0);
	}
	if (dir == 1)
	{
		cub->e_screen->screen = mlx_xpm_file_to_image(cub->mlx, cub->e_screen->paths[1], &cub->e_screen->width, &cub->e_screen->height);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->e_screen->screen, \
			0, 0);
	}
	return (0);
}

int	ft_put_title_screen(t_cub *cub)
{
	int	i;

	i = 0;
	while (!cub->started && i < 4)
	{
		cub->t_screen->screen = mlx_xpm_file_to_image(cub->mlx, \
			cub->t_screen->paths[i], &cub->t_screen->width, \
			&cub->t_screen->height);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->t_screen->screen, \
			0, 0);
		usleep(200000);
		mlx_destroy_image(cub->mlx, cub->t_screen->screen);
		i++;
	}
	return (0);
}
