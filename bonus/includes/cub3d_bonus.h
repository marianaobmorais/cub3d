/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:26:59 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/10 20:50:29 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include "hud_bonus.h"
# include "parser_bonus.h"
# include "image_bonus.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h> //will we use printf?
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <time.h>
# include <limits.h>

/* messages */

# define MSG_MAP "Map: Something is wrong 😕"
# define MSG_TEXTURE "Texture: Something is wrong 😕"
# define MSG_COLOR "Color: Something is wrong 😕"
# define MSG_DUP_COLOR "Color: Something is wrong 😕: Duplicate"

/* colors in hex*/

# define GRAY 0x818d94
# define GRAY_2 0xB1B1B3
# define PINK 0xff00e6
# define YELLOW 0xfff200
# define BLUE 0x030bfc
# define GREEN 0x009c00
# define GREEN2 0xCCFF33
# define RED 0xff1100
# define BLACK 0x000000
# define ORANGE 0XFFA500
# define IGNORE 0x00FFFF

/* measurements */

# define WIDTH 960
# define HEIGHT 600
# define MOVE_SPEED 8
# define ROTATE_SPEED 3
# define MAX_MOVE 70
# define NUM_FRAMES 13
# define FRAME_DELTA 0.016 // ~60 FPS


typedef struct s_hud	t_hud;

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
}	t_sprite;

typedef struct s_draw
{
	int		height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	step;
	double	texture_pos;
}	t_draw;

typedef struct s_door
{
	int				id;
	t_door_status	status;
	t_image			current;
	t_ipoint		tile;
	double			timer;
	int				move;
	t_ipoint		door_tile;
	double			door_dist;
	double			wall_hit;
	int				door_side;
	t_draw			draw;
}	t_door;

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
	bool			sprite_action;
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
	double			eat_time;
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
	bool			hit_door; //door
	int				door_increment;  //door
	t_ipoint		doors_found[10]; //door
	t_image			door_open; //door
	t_image			door_closed; //door
	t_image			doors[13]; //door
	t_image			sprite_still;
	t_image			sprite_move;
	t_image			sprite_eat;
	double			buffer[WIDTH]; //double check this
}	t_raycast;

typedef struct s_cub
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_hud		*hud;
	t_map		*map;
	char		*filepath;
	int			fd;
	bool		started; 
	bool		leaving;
	bool		action;
	int			amount_action;
	double		duration_action;
	t_screen	screens;
	size_t		last_time;
	double		frame_time;
	t_raycast	*raycast;
}	t_cub;

/* ft_init_structs_bonus.c */

void			ft_init_xpm_image(t_cub *cub, t_image *img, char *path);
t_cub			*ft_init_structs(t_cub *cub, char *argv);

/* ft_handle_error_bonus.c */

void			ft_handle_error(const char *error_msg, t_cub *cub);

/* ft_clean_game_bonus.c */

void			ft_clean_game(t_cub *cub);
void			ft_free_vector(char **vector);

/* ft_handle_img_bonus.c */

int				ft_handle_img(t_cub *cub);

/* pixel_utils_bonus.c */

void			ft_put_pixel(t_image *img, int x, int y, int color);
unsigned int	ft_get_pixel_color(t_image *source, int w, int h, t_cub *cub);

/* hook_utils_bonus.c */

int				ft_key_input(int keysym, t_cub *cub);
int				ft_close_window(t_cub *cub);
void			ft_rotate(t_cub *cub, double angle);

/* hook_mouse_bonus.c */
int				ft_mouse_hook(t_cub *cub);

/* move_utils_bonus.c */

void			ft_move_left(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_move_right(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_move_up(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_move_down(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_update_position(t_cub *cub, double tmp_x, double tmp_y);

/* ft_init_raycast_bonus.c */

void			ft_init_raycast(t_cub*cub);

/* ft_render_walls_bonus.c */

void			ft_render_walls(t_cub *cub);
void			ft_define_steps(t_raycast *ray);

/* ft_render_sprites_bonus.c */

void			ft_render_sprites(t_cub *cub);

/* ft_paint_ray_bonus.c */

void			ft_paint_ray(t_cub *cub, int w, t_image texture);

/* ft_dda_bonus.c */

void			ft_dda(t_raycast *ray, t_map *map, bool *hit_wall, t_cub *cub, bool fov);

/* ft_update_doors.c */

void			ft_update_doors(t_cub * cub);
void			ft_open_or_close_door(t_cub *cub);

/* ft_render_doors.c */

int				ft_find_door_index(t_cub *cub, int x, int y);
void			ft_render_doors(t_cub *cub, int w);
void			ft_init_doors(t_cub *cub);
void			ft_clean_doors(t_cub *cub);
void			ft_paint_internal_wall(t_cub *cub, int w);

/* ft_paint_ray_door.c */

void			ft_paint_ray_door(t_cub *cub, int w, t_door door);

int				ft_render_screen(t_cub *cub);

/* ft_draw_sprite.c */

void			ft_draw_sprite(t_cub *cub, t_sprite sprite, int w);


#endif //CUB3D_BONUS_H
