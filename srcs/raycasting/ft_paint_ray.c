#include "../../includes/cub3d.h"

unsigned int	ft_get_pixel_color(t_texture texture, int w, int h)
{
	char	*color;
	int		offset;

	if (!texture.addr || w < 0 || w >= texture.width || h < 0 || h >= texture.height)
		return (0);
	offset = (h * texture.line_len + w * (texture.bpp / 8));
	color = texture.addr + offset;
	//printf("color: %d, ", *color); //debug
	return (*(unsigned int *)color);
}

void	ft_paint_ray(t_cub *cub, int w, t_texture texture)
{
	double			step;
	int				texture_w;
	int				h;
	unsigned int	color;

	step = 1.0 * ((double) texture.height / cub->raycast->wall_height);
	texture_w = cub->raycast->w_pixel * cub->raycast->w_pixel;//texture.width;
	cub->raycast->texture_pixel_pos = (cub->raycast->wall_start - HEIGHT / 2 + cub->raycast->wall_height / 2) * step;
	h = cub->raycast->wall_start;
	while (h <= cub->raycast->wall_end)
	{
		cub->raycast->texture_pixel_pos += step;
		color = ft_get_pixel_color(texture, w, h);
		//if (color == 0)
		ft_put_pixel(cub->image, w, h, color);
		h++;
	}
}
