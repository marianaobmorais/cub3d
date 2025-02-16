# ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

/* measurements */

# define MINI_WIDTH 90
# define MINI_HEIGHT 75

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

/* ft_put_minimap.c */

void	ft_put_minimap(t_cub *cub);

/* minimap_utils.c */

void	ft_put_square(t_image *img, int x, int y, int color);
void	ft_set_limit_x(t_cub *cub, int map_width);
void	ft_set_limit_y(t_cub *cub, int map_height);

/* ft_init_minimap.c */

void	ft_init_minimap(t_cub *cub);

# endif //MINIMAP_H
