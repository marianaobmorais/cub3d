#include "../../includes/cub3d_bonus.h"

static void	ft_paint_on_image(t_cub *cub, t_image *source, t_ipoint pos, double t)
{
	int	source_color;
	int	default_color;
	int	blend;
	int	y;
	int	x;

	x = 0;
	while (x < source->height)
	{
		y = 0;
		while (y < source->width)
		{
			default_color = ft_get_pixel_color(cub->image, x + pos.x, y + pos.y, cub);
			source_color = ft_get_pixel_color(source, x, y, cub);
			blend = ft_blendcolors(default_color, source_color, t);
			if (source_color == IGNORE) //color to ignore
				ft_put_pixel(cub->image, x + pos.x, y + pos.y, default_color);
			else
				ft_put_pixel(cub->image, x + pos.x, y + pos.y, blend);
			y++;
		}
		x++;
	}
}

void	ft_render_action(t_cub *cub)
{
	//add brief
	t_ipoint	pos;

	if (cub->action)
	{
		pos.x = 200;
		pos.y = HEIGHT - cub->hud->breadcrumbs.height;
		ft_paint_on_image(cub, &cub->hud->breadcrumbs, pos, cub->duration_action);
		cub->duration_action += cub->frame_time;
		if (cub->duration_action >= 0.5)
		{
			cub->action = false;
			cub->duration_action = 0;
		}
	}
	if (cub->raycast->sprite_action)
	{
		cub->raycast->eat_time += cub->frame_time;
		if (cub->raycast->eat_time >= 5)
		{
			cub->raycast->sprite_action = false;
			cub->raycast->eat_time = 0;
		}
	}
}
