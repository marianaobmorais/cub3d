/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:17:20 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/02 11:12:44 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_BONUS_H
# define HUD_BONUS_H

# include <math.h>
# include "image_bonus.h"

# define MINI_WIDTH 87
# define MINI_HEIGHT 52
# define TILE 5
# define OFFSET_X (9 * TILE)
# define OFFSET_Y (4 * TILE)
# define FOV (M_PI / 3)
# define BREAD_1 8
# define BREAD_2 16
# define BREAD_3 24

typedef struct s_cub	t_cub;
typedef struct s_dpoint	t_dpoint;

typedef struct s_screen
{
	t_image		start_0;
	t_image		start_1;
	t_image		start_2;
	t_image		start_3;
	t_image		end_0;
	t_image		end_1;
	int			current_screen;
}	t_screen;

typedef struct s_hud
{
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	t_image		watch;
	t_image		viewmodel_0;
	t_image		viewmodel_1;
	t_image		viewmodel_2;
	t_image		viewmodel_3;
	t_image		viewmodel_4;
	t_image		bread;
	t_image		empty_bread;
	t_image		breadcrumbs;
	t_image		door;
	t_dpoint	*ray_hits;
}	t_hud;


/* ft_init_hud.c */

void	ft_clean_hud(t_cub *cub);
void	ft_init_hud(t_cub *cub);

/* ft_render_minimap_on_hud.c */

void	ft_render_minimap_on_hud(t_cub *cub);

/* ft_render_minimap_utils.c */

void	ft_put_square(t_image *img, int x, int y, int color);
void	ft_set_limit_x(t_cub *cub, int map_width);
void	ft_set_limit_y(t_cub *cub, int map_height);
void	ft_put_player(t_image *img, int x, int y, int color);

/* ft_render_source_on_hud.c */

void	ft_render_source_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y);

/* screens.c */

void	ft_init_screens(t_cub *cub);
void	ft_clean_screens(t_cub *cub);
int		ft_put_end_screen(t_cub *cub, int dir);
void	ft_put_start_screen(t_cub *cub);

int		ft_render_screen(t_cub *cub);

/* colors_utils.c */

int		ft_blendcolors(int color1, int color2, float alpha);
void	draw_line_minimap(t_cub *cub, int x1, int y1, int x2, int y2, int color);
void	ft_paint_action_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y);
void	ft_render_fov_minimap(t_cub *cub);

void	ft_render_action(t_cub *cub);
void	ft_hextoarray(int hex, unsigned char *rgb);
void	ft_door(t_cub *cub, t_image *source, int pos_x, int pos_y);


void	ft_render_fov_minimap(t_cub *cub);
void	ft_render_viewmodel(t_cub *cub);


# endif //HUD_BONUS_H