#include "../../includes/cub3d.h"

void	ft_render_walls(t_image *img, t_map *map)
{
	(void)img;
	(void)map;
	//int	factor; //aka multiplier
	int	x; //number of the pixel used

	x = 0;
	while (x < WIDTH)
	{
		//factor = 2 * (x / WIDTH) - 1;

		ft_put_pixel(img, x, (HEIGHT / 2) - 5, YELLOW);
		x++;
	}

}
