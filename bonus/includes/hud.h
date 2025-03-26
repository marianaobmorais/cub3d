# ifndef HUD_H
# define HUD_H

# include "cub3d_bonus.h"

/* measurements */

# define MINI_WIDTH 87
# define MINI_HEIGHT 52
# define TILE 5
# define OFFSET_X (9 * TILE)
# define OFFSET_Y (4 * TILE)
# define FOV (M_PI / 3)
# define BREAD_1 5
# define BREAD_2 (BREAD_1 * 2)
# define BREAD_3 (BREAD_1 * 3)

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
	t_image		*bread;
	t_image		*empty_bread;
	t_image		*breadcrumbs;
	t_image		*door;
	t_dpoint	*ray_hits;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
}	t_hud;


/* ft_init_hud.c */

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

void	ft_init_start_screen(t_cub *cub);
void	ft_init_end_screen(t_cub *cub);
int		ft_render_screen(t_cub *cub);
int		ft_put_end_screen(t_cub *cub, int dir);

/* stuffs */

int		ft_blendcolors(int color1, int color2, float alpha);
void	draw_line_minimap(t_cub *cub, int x1, int y1, int x2, int y2, int color);
void	ft_paint_action_on_hud(t_cub *cub, t_image *source, int pos_x, int pos_y);
void	ft_render_fov_minimap(t_cub *cub);
void	ft_render_action(t_cub *cub);
void	ft_hextoarray(int hex, unsigned char *rgb);
void	ft_door(t_cub *cub, t_image *source, int pos_x, int pos_y);


void	ft_render_fov_minimap(t_cub *cub);

# endif //HUD_H