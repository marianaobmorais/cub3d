#include "../includes/cub3d.h"

void	ft_put_pixel(t_image *img, int x, int y, int color)
{
	//add brief
	int	offset;

	offset = 0;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->addr)) = color;
}
