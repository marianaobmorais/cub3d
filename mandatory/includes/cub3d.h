/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:26:59 by mariaoli          #+#    #+#             */
/*   Updated: 2025/03/22 20:12:05 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "../../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h> //will we use printf?
# include <stdlib.h>
//# include <sys/time.h> //do we use this?
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h> //bonus
# include <time.h> //bonus
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
# define RED 0xff1100
# define BLACK 0x000000
# define IGNORE 0x00FFFF

/* measurements */

# define WIDTH 960
# define HEIGHT 600
# define MOVE_SPEED 0.2913

typedef enum e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}	t_directions;

typedef enum e_parser_status
{
	ERROR,
	BUFFER,
	NO_BUFFER
}	t_parser_status;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_ipoint;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_raycast
{
	t_dpoint		player_pos;
	t_dpoint		player_dir;
	t_dpoint		camera_plane;
	t_dpoint		ray_dir;
	t_ipoint		player_squ;
	t_ipoint		step;
	t_ipoint		step_squ;
	double			factor;
	double			delta_dist_x;
	double			delta_dist_y;
	double			dist_to_x;
	double			dist_to_y;
	double			perp_wall_dist;
	double			move_speed;
	double			wall_hit_value;
	double			texture_pos;
	int				wall_height;
	int				wall_start;
	int				wall_end;
	t_directions	hit_side;
	t_image			north_texture;
	t_image			south_texture;
	t_image			east_texture;
	t_image			west_texture;
}	t_raycast;

typedef struct s_map
{
	char			**matrix;
	char			**matrix_tmp;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	unsigned char	*floor_rgb;
	unsigned char	*ceiling_rgb;
	int				floor_hex;
	int				ceiling_hex;
	int				player_squ_x;
	int				player_squ_y;
	int				width;
	int				height;
	t_directions	direction;
}	t_map;

typedef struct s_cub
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_map		*map;
	char		*filepath;
	int			fd;
	t_raycast	*raycast;
}	t_cub;

/* ft_init_structs.c */

t_cub			*ft_init_structs(t_cub *cub, char *argv);

/* ft_handle_error.c */

void			ft_handle_error(const char *error_msg, t_cub *cub);

/* ft_clean_game.c */

void			ft_clean_game(t_cub *cub);
void			ft_free_vector(char **vector);

/* PARSER */

/* ft_loadmap.c */

void			ft_load_map(char *const filepath, t_cub *cub);

/* ft_map_parser.c */

void			ft_map_parser(int fd, t_cub *cub, int i);

/* ft_map_parser_utils.c */

char			*ft_buffer(char *buffer, char *line, int start, t_cub *cub);
t_parser_status	ft_add_texture(char *line, t_cub *game, char *identifier, \
	t_directions direction);
char			**ft_safe_split(char *buffer, t_cub *cub);
	
/* parser_utils.c */

bool			ft_access(char *filepath);
bool			ft_is_ext(char *filename, char *ext);
int				ft_isspace(int c, int mode);
char			*ft_strip(char *str, int mode);
void	ft_print_map(t_map *map); //debug

/* ft_fill_matrix.c */

void			ft_fill_matrix(t_cub *cub);

/* ft_matrix_parser.c */

int				ft_isnumeric(char *nbr);
void			ft_matrix_parser(t_cub *cub, char **matrix);

/* ft_matrix_parser_utils.c */

int				ft_arraytohex(unsigned char *rgb);
int				ft_is_empty(char *line);
bool			ft_valid_wall(char *line, char *previous_line, \
	bool first_or_last);

/* ft_handle_img.c */

void			ft_handle_img(t_cub *cub);

/* pixel_utils.c */

void			ft_put_pixel(t_image *img, int x, int y, int color);
unsigned int	ft_get_pixel_color(t_image *source, int w, int h, t_cub *cub);

/* hook_utils.c */

int				ft_key_input(int keysym, t_cub *cub);
int				ft_close_window(t_cub *cub);

/* move_utils.c */

void			ft_move_left(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_move_right(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_move_up(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_move_down(t_cub *cub, double *tmp_x, double *tmp_y);
void			ft_update_position(t_cub *cub, double tmp_x, double tmp_y);

/* ft_init_raycast.c */

void			ft_init_raycast(t_cub*cub);

/* ft_render_walls.c */

void			ft_render_walls(t_cub *cub);

/* ft_paint_ray.c */

void			ft_paint_ray(t_cub *cub, int w, t_image texture);

/* ft_dda.c */

void			ft_dda(t_raycast *ray, t_map *map, bool *hit_wall);

#endif //CUB3D_H
