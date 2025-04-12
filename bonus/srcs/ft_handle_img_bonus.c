/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_img_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:57 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/12 18:04:07 by joneves-         ###   ########.fr       */
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
 * @brief Updates sprite actions over time (e.g. eating animation).
 *
 * Iterates through all sprites in the map and, if a sprite is performing 
 * an action, increments its action timer (`eat_time`) using the frame time. 
 * Once the action duration reaches or exceeds 4 seconds, the action is 
 * stopped and the timer is reset.
 *
 * @param cub Pointer to the main game context containing map and frame data.
 */
void	ft_sprite_action(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map->sprite_count)
	{
		if (cub->map->sprite[i].sprite_action)
			cub->map->sprite[i].eat_time += cub->frame_time;
		if (cub->map->sprite[i].eat_time >= 4)
		{
			cub->map->sprite[i].sprite_action = false;
			cub->map->sprite[i].eat_time = 0;
		}
		i++;
	}
}

/**
 * @brief Manages frame timing and triggers rendering stages.
 *
 * Calculates the time elapsed since the last frame and determines which 
 * rendering actions should be performed. If the game has not started and 
 * sufficient time has passed, the start screen is displayed. If the game 
 * has started and the player is not exiting, it proceeds to render the 
 * frame, including the scene and sprite actions, based on the frame timing.
 *
 * @param cub Pointer to the main game context with timing and render data.
 * @return Always returns 0.
 */
int	ft_render_screen(t_cub *cub)
{
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
	if (cub->started && !cub->leaving && cub->frame_time >= 0.016)
	{
		ft_render_action(cub);
		ft_sprite_action(cub);
		cub->last_time = now;
	}
	return (0);
}
