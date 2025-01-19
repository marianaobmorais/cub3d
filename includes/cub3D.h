# ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>

# define MSG_TEXTURE_EXT
# define MSG_TEXTURE_FILE
# define MSG_TEXTURE_ARG
# define MSG_TEXTURE_DUP
# define MSG_MAP_EXT

typedef struct s_map
{
	char			**map;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	unsigned char	*floor_rgb;
	unsigned char	*ceiling_rgb;
	int				player_pos_h;
	int				player_pos_w;
}	t_map;

typedef struct s_cub
{
	char	*filepath;
	int		fd;
	t_map	*map;
}	t_cub;

typedef enum e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}	t_directions;

/* ft_handle_error.c */

void	ft_handle_error(const char *error_msg, t_cub *cub);
void	ft_clean_cub(t_cub *cub);

/* ft_loadmap.c */

void	ft_loadmap(char *const filepath, t_cub *cub);

/* ft_loadmap_utils.c */

void	ft_add_texture(char *line, t_cub *cub, char *identifier, \
	t_directions direction);
void	ft_add_color(char *line, t_cub *cub, char *identifier, \
	t_directions direction);
void	ft_add_map(char *line, t_cub *cub);

/* toolbox.c */

bool	ft_access(char *filepath);
bool	ft_is_ext(char *filename, char *ext);
char	*ft_strip(char *str);
int		ft_isspace(int c);
void	ft_free_vector(char **vector);

# endif //CUB3D_H
