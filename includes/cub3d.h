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

# define PIXEL 100 //32

typedef struct	s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct	s_game
{
	void	*mlx;
	void	*window;
	//t_map	*map;
	t_image	*img;
}	t_game;


//ft_init.c

t_game	*ft_init_game(/* t_map *map */);
t_image	*ft_init_image(t_game *game);

//hook_utils.c

int	ft_key_input(int keysym, t_game *game);
int	ft_close_window(t_game *game);

# endif //CUB3D_H
