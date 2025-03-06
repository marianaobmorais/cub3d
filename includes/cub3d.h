# ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "hud.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h> //do we use this?
# include <stdlib.h>
//# include <unistd.h> //duplicated from libft
# include <sys/time.h> //do we use this?
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
//# define PIXEL 100 //32

/* colors in hex*/

# define GRAY 0x818d94
# define PINK 0xff00e6
# define YELLOW 0xfff200
# define BLUE 0x030bfc
# define GREEN 0x009c00
# define RED 0xff1100

/* measurements */

# define PIXEL 1
# define WIDTH 960
# define HEIGHT 600

typedef struct s_minimap	t_minimap; //bonus

typedef enum e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}	t_directions;

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
	//double			frame_time;
	//double			last_frame_time;
	double			delta_dist_x;
	double			delta_dist_y;
	double			dist_to_x;
	double			dist_to_y;
	double			perp_wall_dist;
	double			move_speed;
	t_directions	hit_side;
	int				wall_height;
	int				wall_start;
	int				wall_end;
}	t_raycast;

typedef struct s_map
{
	char			**matrix;
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
	t_directions	direction;
}	t_map;

typedef struct	s_image

{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_cub
{
	void			*mlx;
	void			*window;
	t_image			*image;
	t_minimap		*mini;
	t_map			*map;
	char			*filepath;
	int				fd;
	bool			started; //screen
	bool			leaving; //screen
	t_screen	*start_screen; //screen
	t_screen	*end_screen; //screen
	t_raycast	*raycast;
}	t_cub;


/* ft_init_structs.c */

t_cub	*ft_init_structs(t_cub *cub, char *argv);

/* ft_handle_error.c */

void	ft_handle_error(const char *error_msg, t_cub *game);

/* ft_clean_game.c */

void	ft_clean_game(t_cub *game);
void	ft_free_vector(char **vector);

/* ft_loadmap.c */

void	ft_load_map(char *const filepath, t_cub *game);

/* ft_map_parser.c */

void	ft_map_parser(int fd, t_cub *game);

/* ft_map_parser_utils.c */

char	*ft_buffer(char *buffer, char *line, int start, t_cub *game);
void	ft_add_texture(char *line, t_cub *game, char *identifier, \
	t_directions direction);

/* parser_utils.c */

bool	ft_access(char *filepath);
bool	ft_is_ext(char *filename, char *ext);
char	*ft_strip(char *str);
int		ft_isspace(int c);
int		ft_isnumeric(char *nbr);
int		ft_arraytohex(unsigned char *rgb);
void	ft_print_map(t_map *map); //debug

/* ft_matrix_parser.c */

void	ft_matrix_parser(t_cub *game, char **matrix);

/* ft_matrix_parser_utils.c */

int		ft_is_empty(char *line);
bool	ft_valid_wall(char *line);

/* ft_run_game.c */

void	ft_run_game(t_cub *cub);
void	ft_put_image(t_cub *cub);
void	ft_put_minimap(t_cub *cub);

/* ft_put_pixel.c */

void	ft_put_pixel(t_image *img, int x, int y, int color);

/* hook_utils.c */

int		ft_key_input(int keysym, t_cub *game);
int		ft_close_window(t_cub *game);

void	ft_put_image(t_cub *cub);

/* ft_init_raycast.c */

void	ft_init_raycast(t_cub*cub);

/* ft_render_walls.c */

void	ft_render_walls(t_cub *cub);

/* ft_dda.c */

void	ft_dda(t_raycast *ray, t_map *map, bool *hit_wall);

# endif //CUB3D_H
