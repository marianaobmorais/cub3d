/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_ray_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:09:35 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/04 19:15:25 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Paints a vertical strip of a wall texture onto the screen.
 * 
 * This function takes the calculated texture coordinates and maps them to a
 * vertical stripe on the screen at the given window width. It adjusts the
 * texture coordinates for wall orientation and ensures they remain within
 * bounds. Then, it iterates over the vertical segment of the screen, sampling
 * texture colors and placing pixels accordingly.
 * 
 * @param cub The main structure containing game and rendering data.
 * @param window_w The x-coordinate of the vertical stripe in the window.
 * @param texture The texture image to apply.
 */
void	ft_paint_ray(t_cub *cub, int window_w, t_image texture)
{
	double			step;
	int				texture_w;
	int				texture_h;
	int				window_h;
	unsigned int	color;

	texture_w = (int)(cub->raycast->wall_hit_value * (double)texture.width);
	if (cub->raycast->hit_side == SOUTH)
		texture_w = texture.width - texture_w - 1;
	if (cub->raycast->hit_side == EAST)
		texture_w = texture.width - texture_w - 1;
	texture_w = texture_w % texture.width;
	step = 1.0 * ((double) texture.height / cub->raycast->wall_height);
	cub->raycast->texture_pos = (cub->raycast->wall_start - HEIGHT / 2
			+ cub->raycast->wall_height / 2) * step;
	window_h = cub->raycast->wall_start;
	while (window_h <= cub->raycast->wall_end)
	{
		texture_h = (int)cub->raycast->texture_pos % texture.height;
		cub->raycast->texture_pos += step;
		color = ft_get_pixel_color(&texture, texture_w, texture_h, cub);
		ft_put_pixel(cub->image, window_w, window_h, color);
		window_h++;
	}
}

void	ft_paint_ray_door(t_cub *cub, int w, t_image texture,
	double dist, int side, double wall_hit)
{
	int		tex_x;
	int		tex_y;
	int		draw_start;
	int		draw_end;
	double	texture_pos;
	double	step;
	int		door_height;
	int		y;
	int		color;

	door_height = (int)(HEIGHT / dist);
	draw_start = -door_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = door_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

	// tex_x (coluna da textura)
	tex_x = (int)(wall_hit * texture.width);
	if ((side == 0 && cub->raycast->ray_dir.x > 0) || (side == 1 && cub->raycast->ray_dir.y < 0))
		tex_x = texture.width - tex_x - 1;
	tex_x %= texture.width;

	// passo vertical por pixel
	step = (double)texture.height / door_height;
	texture_pos = (draw_start - HEIGHT / 2 + door_height / 2) * step;

	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)texture_pos % texture.height;
		texture_pos += step;

		color = ft_get_pixel_color(&texture, tex_x, tex_y, cub);
		if (color != IGNORE)
			ft_put_pixel(cub->image, w, y, color);
		y++;
	}
}
