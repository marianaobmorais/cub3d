#include "../../includes/cub3d_bonus.h"

static void	ft_prepare_door_draw(t_cub *cub, t_door *door)
{
	t_draw	*draw;

	draw = &door->draw;
	draw->height = (int)(HEIGHT / door->door_dist);
	draw->draw_start = -draw->height / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->height / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
	draw->tex_x = (int)(door->wall_hit * door->current.width);
	if ((door->door_side == 0 && cub->raycast->ray_dir.x > 0)
		|| (door->door_side == 1 && cub->raycast->ray_dir.y < 0))
		draw->tex_x = door->current.width - draw->tex_x - 1;
	draw->tex_x %= door->current.width;
	draw->step = (double)door->current.height / draw->height;
	draw->texture_pos = (draw->draw_start - HEIGHT / 2 + draw->height / 2) \
		* draw->step;
}

void	ft_paint_ray_door(t_cub *cub, int w, t_door door)
{
	t_draw	*draw;
	int		y;
	int		tex_y;
	int		color;

	draw = &door.draw;
	ft_prepare_door_draw(cub, &door);
	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		tex_y = (int)(draw->texture_pos);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= door.current.height)
			tex_y = door.current.height - 1;
		draw->texture_pos += draw->step;

		color = ft_get_pixel_color(&door.current, draw->tex_x, tex_y, cub);
		if (color != IGNORE)
			ft_put_pixel(cub->image, w, y, color);
		y++;
	}
}
