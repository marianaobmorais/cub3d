/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:14:42 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/11 17:59:35 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_BONUS_H
# define RAYCASTING_BONUS_H

# include "image_bonus.h"

typedef struct s_sprite
{
	int			id;
	int			order;
	int			screen_w;
	int			relative_width;
	int			relative_height;
	int			start_h;
	int			end_h;
	int			start_w;
	int			end_w;
	t_ipoint	tile;
	t_dpoint	pos;
	t_dpoint	transform;
	t_image		img;
	double		dist;
	bool		status;
	bool		sprite_action;
	bool		near_player; //test
	double		eat_time;
}	t_sprite;

typedef struct s_raycast
{
	t_dpoint		player_pos;
	t_dpoint		player_dir;
	t_dpoint		camera_plane;
	t_dpoint		ray_dir;
	t_ipoint		player_tile;
	t_ipoint		step;
	t_ipoint		step_tile;
	t_ipoint		mouse_pos;
	bool			mouse_status;
	double			move_speed;
	double			rotate_speed;
	double			factor;
	double			delta_dist_x;
	double			delta_dist_y;
	double			dist_to_x;
	double			dist_to_y;
	double			perp_wall_dist;
	double			wall_hit_value;
	double			texture_pos;
	double			time;
	double			mouse_time;
	int				hit_side;
	int				wall_height;
	int				wall_start;
	int				wall_end;
	t_image			north_texture;
	t_image			south_texture;
	t_image			east_texture;
	t_image			west_texture;
	t_image			grab_go;
	t_image			grab_go2;
	bool			hit_door;
	int				door_increment;
	t_ipoint				doors_found[10]; //dynamic allocation?
	t_image			door_open;
	t_image			door_closed;
	t_image			doors[13];
	t_image			sprite_still;
	t_image			sprite_move;
	t_image			sprite_eat;
	double			buffer[WIDTH]; //double check this
}	t_raycast;

/* ft_init_raycast_bonus.c */

void			ft_init_raycast(t_cub*cub);

/* ft_render_walls_bonus.c */

void			ft_render_walls(t_cub *cub);
void			ft_define_steps(t_raycast *ray);

/* ft_render_sprites_bonus.c */

void			ft_render_sprites(t_cub *cub);

/* ft_render_sprites_utils_bonus.c */

void		ft_paint_external_wall(t_cub *cub, int w);

/* ft_paint_ray_bonus.c */

void			ft_paint_ray(t_cub *cub, int w, t_image texture);

/* ft_dda_bonus.c */

void			ft_dda(t_raycast *ray, t_map *map, bool *hit_wall, t_cub *cub, bool fov);

void	ft_sprite_action(t_cub *cub);

#endif //RAYCASTING_BONUS_H