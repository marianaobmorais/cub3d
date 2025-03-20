# ifndef HUD_H
# define HUD_H

# include "cub3d.h"

/* measurements */

# define MINI_WIDTH 87
# define MINI_HEIGHT 52
# define MINIMAP_SCALE_X 0.090625
# define MINIMAP_SCALE_Y 0.086666

typedef struct s_cub	t_cub;
typedef struct s_image	t_image;
typedef struct s_dpoint	t_dpoint;

typedef struct s_screen
{
	void	*img;
	char	**paths;
	int		width;
	int		height;
}	t_screen;

typedef struct s_hud
{
	t_image		*img;
	t_image		*watch;
	t_image		*viewmodel;
	t_image		*breads;
	t_image		*breadcrumbs;
	t_image		*door;
	t_dpoint	*ray_hits;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
}	t_hud;


/* ft_paint_minimap.c */

void	ft_paint_minimap_on_hud(t_cub *cub);

/* minimap_utils.c */

void	ft_put_square(t_image *img, int x, int y, int color);
void	ft_set_limit_x(t_cub *cub, int map_width);
void	ft_set_limit_y(t_cub *cub, int map_height);
void	ft_put_player(t_image *img, int x, int y, int color);

void	ft_init_hud(t_cub *cub);
void	ft_put_hud(t_cub *cub);
int		ft_get_pixel_color(int x, int y, t_image *source); //organizar
void	ft_paint_source_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y);
void	ft_paint_action_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y);

/* screens.c */

void	ft_init_screen(t_cub *cub);
int		ft_put_start_screen(t_cub *cub);
int		ft_put_end_screen(t_cub *cub, int dir);

int		ft_blendcolors(int color1, int color2, float alpha);
void	draw_line_minimap(t_cub *cub, int x1, int y1, int x2, int y2, int color);

# endif //HUD_H