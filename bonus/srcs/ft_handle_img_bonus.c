/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_img_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:57 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/06 11:08:42 by joneves-         ###   ########.fr       */
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
	ft_render_bg(cub->image, cub->map->ceiling_hex, cub->map->floor_hex);
	update_doors(cub);
	ft_render_walls(cub);
	//ft_render_sprites(cub); //sprites	
	//ft_render_door(cub, (cub->map->door)[0]);
	ft_render_source_on_hud(cub, &cub->hud->watch, 0, 0); //bonus
	ft_render_minimap_on_hud(cub); //bonus
	ft_render_viewmodel(cub);
	//update speed
	cub->raycast->move_speed = cub->frame_time * MOVE_SPEED;
	cub->raycast->rotate_speed = cub->frame_time * ROTATE_SPEED;
	ft_mouse_hook(cub); //mouse
	mlx_put_image_to_window(cub->mlx, cub->window, cub->image->img_ptr, 0, 0);
	return (0);
}

/**
 * @brief Retrieves the current time in milliseconds.
 * 
 * This function uses `gettimeofday` to obtain the current time and converts 
 * it into milliseconds. It is typically used for frame timing calculations.
 * 
 * @return The current time in milliseconds.
 */
static size_t	ft_get_time(void)
{
	size_t			milliseconds;
	struct timeval	time;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

/**
 * @brief Displays the start screen of the game with changing images.
 *
 * This function controls the display of a start screen sequence by cycling 
 * through images at a regular interval (every 0.2 seconds). It updates the 
 * image shown on the screen and ensures smooth transitions between the 
 * images. Once all images have been displayed, the cycle restarts.
 *
 * @param cub Pointer to the main game structure.
 * @return 0 upon completion.
 */
int	ft_render_screen(t_cub *cub)
{
	//update brief
	size_t		now;

	now = ft_get_time();
	cub->frame_time = (now - cub->last_time) / 1000.0;
	if (!cub->started && cub->frame_time >= 0.2)
	{
		ft_put_start_screen(cub);
		cub->last_time = now;
	}
	if (cub->started && !cub->leaving && cub->frame_time >= 0.016)
	{
		ft_handle_img(cub);
		cub->last_time = now;
	}
	if (cub->action && cub->frame_time >= 0.016)
	{
		ft_render_action(cub);
		cub->last_time = now;
	}
	return (0);
	//rename this file? suggestion: ft_render_screen.c
}