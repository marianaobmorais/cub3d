/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_img_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamorais <marianamorais@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:57 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/06 18:44:24 by marianamora      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Paints a horizontal line in the background.
 *
 * This function fills a single horizontal line (row) of pixels in the image 
 * with the specified color.
 *
 * @param img Pointer to the image structure containing the buffer.
 * @param y The y-coordinate of the row to paint.
 * @param color The color value to fill the row with.
 */
static void	ft_paint_bg(t_image *img, int y, int color)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ft_put_pixel(img, x, y, color);
		x++;
	}
}

/**
 * @brief Renders the background by filling the ceiling and floor colors.
 *
 * This function iterates through the image's height, painting the top half 
 * with the ceiling color and the bottom half with the floor color.
 *
 * @param img Pointer to the image structure.
 * @param ceiling_color The color value for the ceiling.
 * @param floor_color The color value for the floor.
 */
static void	ft_render_bg(t_image *img, int ceiling_color, int floor_color)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y <= HEIGHT / 2)
			ft_paint_bg(img, y, ceiling_color);
		else
			ft_paint_bg(img, y, floor_color);
		y++;
	}
}

/**
 * @brief Handles the rendering of the game frame.
 *
 * This function updates the background, renders walls, 
 * draws the HUD (Heads-Up Display), and displays the final image in the
 * game window.
 *
 * @param cub Pointer to the main game structure.
 * @return Always returns 0.
 */
int	ft_handle_img(t_cub *cub)
{
	//add frames
	//update brief
	ft_render_bg(cub->image, cub->map->ceiling_hex, cub->map->floor_hex);
	ft_render_walls(cub);
	ft_render_sprites(cub); //sprites
	ft_render_source_on_hud(cub, &cub->hud->watch, 0, 0); //bonus
	if (cub->amount_action < BREAD_3 + 1)
		ft_render_source_on_hud(cub, &cub->hud->viewmodel, 390, 420); //bonus
	if (cub->amount_action > BREAD_1)
		ft_render_source_on_hud(cub, &cub->hud->empty_bread, WIDTH - 128, 0); //bonus
	else
		ft_render_source_on_hud(cub, &cub->hud->bread, WIDTH - 128, 0); //bonus
	if (cub->amount_action > BREAD_2)
		ft_render_source_on_hud(cub, &cub->hud->empty_bread, WIDTH - 192, 0); //bonus
	else
		ft_render_source_on_hud(cub, &cub->hud->bread, WIDTH - 192, 0); //bonus
	if (cub->amount_action > BREAD_3)
		ft_render_source_on_hud(cub, &cub->hud->empty_bread, WIDTH - 256, 0); //bonus
	else
		ft_render_source_on_hud(cub, &cub->hud->bread, WIDTH - 256, 0); //bonus
	//update speed
	cub->raycast->move_speed = cub->frame_time * MOVE_SPEED;
	cub->raycast->rotate_speed = cub->frame_time * ROTATE_SPEED;
	if (!cub->raycast->mouse_status)
		ft_mouse_hook(cub); //mouse
	//ft_door(cub, cub->hud->door, WIDTH / 2 - 0, HEIGHT / 2 - 70); //bonus //move to render_wall?
	//ft_render_minimap_on_hud(cub); //bonus
	mlx_put_image_to_window(cub->mlx, cub->window, cub->image->img_ptr, 0, 0);
	return (0);
}
