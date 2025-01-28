#include "../../includes/cub3d.h"

// void	ft_background(unsigned char *rgb, int width, int height, t_cub *cub)
// {
// 	int	i;

// 	i = 0;
// 	while (i)
// 	{
// 		mlx_pixel_put(cub->mlx, cub->window, 120, 100, 0x00FFFF);
// 		i++;
// 	}
// }

void	ft_put_string(char *str, t_cub *cub)
{
	mlx_string_put(cub->mlx, cub->window, 160, 100, 0x00FFFF, str);

	int x = 0;
	int y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(cub->mlx, cub->window, x, y, 0x00FFFF);
			x++;
		}
		y++;
	}
}
