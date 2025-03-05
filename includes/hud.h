# ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

/* measurements */

# define MINI_WIDTH 85
# define MINI_HEIGHT 50

typedef struct s_cub	t_cub;
typedef struct s_image	t_image;

typedef struct s_minimap
{
	char	*texture;
	t_image	*img_minimap;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	void	*img_texture;
}	t_minimap;

typedef struct s_title_screen
{
	void	*screen;
	char	**paths;
	int		width;
	int		height;
}	t_title_screen;

/* ft_put_minimap.c */

void	ft_put_minimap(t_cub *cub);

/* minimap_utils.c */

void	ft_put_square(t_image *img, int x, int y, int color);
void	ft_set_limit_x(t_cub *cub, int map_width);
void	ft_set_limit_y(t_cub *cub, int map_height);

/* ft_init_minimap.c */

void	ft_init_minimap(t_cub *cub);


void	ft_background(t_cub *cub);

int		ft_put_title_screen(t_cub *cub);
void	ft_init_title_screen(t_cub *cub);
int		ft_put_end_screen(t_cub *cub, int dir);

# endif //MINIMAP_H
