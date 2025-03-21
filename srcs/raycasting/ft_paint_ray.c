#include "../../includes/cub3d.h"

// static unsigned int	ft_get_pixel_color(t_image source, int w, int h)
// {
// 	char	*color;
// 	int		offset;

// 	if (!source.addr || w < 0 || w >= source.width || h < 0 || h >= source.height)
// 		return (0);
// 	offset = (h * source.line_len + w * (source.bpp / 8));
// 	color = source.addr + offset;
// 	//printf("color: %d, ", *color); //debug
// 	return (*(unsigned int *)color);
// }

void	ft_paint_ray(t_cub *cub, int window_w, t_image texture)
{
	double			step;
	int				texture_w;
	int				texture_h;
	int				window_h;
	unsigned int	color;

	//texture_w (texX) is the x-coordinate of the texture. this coordinate will remain the same, 
	//because we stay in the same vertical stripe of the screen.
	texture_w = (int)(cub->raycast->wall_hit_value * (double)texture.width);
	if (cub->raycast->hit_side == SOUTH)
		texture_w = texture.width - texture_w - 1; //x coordinate on the texture
	if (cub->raycast->hit_side == EAST)
		texture_w = texture.width - texture_w - 1; //x coordinate on the texture


	step = 1.0 * ((double) texture.height / cub->raycast->wall_height);
	cub->raycast->texture_pos = (cub->raycast->wall_start - HEIGHT / 2 + cub->raycast->wall_height / 2) * step;
	window_h = cub->raycast->wall_start;
	while (window_h <= cub->raycast->wall_end)
	{
		texture_h = (int)cub->raycast->texture_pos & (texture.height - 1); //study this
		cub->raycast->texture_pos += step;
		color = ft_get_pixel_color(texture, texture_w, texture_h);
		ft_put_pixel(cub->image, window_w, window_h, color);
		window_h++;
	}
}
