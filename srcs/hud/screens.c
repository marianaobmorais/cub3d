#include "../../includes/cub3d.h"

void	ft_init_screen(t_cub *cub)
{
	cub->started = false;
	cub->leaving = false;
	cub->start_screen->img = NULL;
	cub->start_screen->width = WIDTH;
	cub->start_screen->height = HEIGHT;
	cub->start_screen->paths = malloc(sizeof(char *) * 4);
	if (!cub->start_screen->paths)
		ft_handle_error("malloc: cub->start_screen->paths", cub);
	cub->start_screen->paths[0] = "assets/textures/start_screen0.xpm";
	cub->start_screen->paths[1] = "assets/textures/start_screen1.xpm";
	cub->start_screen->paths[2] = "assets/textures/start_screen2.xpm";
	cub->start_screen->paths[3] = "assets/textures/start_screen3.xpm";
	cub->end_screen->img = NULL;
	cub->end_screen->width = WIDTH;
	cub->end_screen->height = HEIGHT;
	cub->end_screen->paths = malloc(sizeof(char *) * 2);
	if (!cub->end_screen->paths)
		ft_handle_error("malloc: cub->end_screen->paths", cub);
	cub->end_screen->paths[0] = "assets/textures/end_screen0.xpm";
	cub->end_screen->paths[1] = "assets/textures/end_screen1.xpm";
}

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

int	ft_put_start_screen(t_cub *cub)
{
	int	i;

	i = 0;
	while (!cub->started && i < 4)
	{
		cub->start_screen->img = mlx_xpm_file_to_image(cub->mlx, \
			cub->start_screen->paths[i], &cub->start_screen->width, \
			&cub->start_screen->height);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->start_screen->img, \
			0, 0);
		usleep(200000);
		if (cub->start_screen->img)
			mlx_destroy_image(cub->mlx, cub->start_screen->img);
		i++;
	}
	return (0);
}
