#include "../includes/cub3d.h"

int	ft_close_window(t_cub *cub)
{
	ft_clean_cub(cub);
	exit(0);
}

int	ft_key_input(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		ft_close_window(cub);
/* 	if (keysym == XK_A || keysym == XK_a)
		; //left
	if (keysym == XK_D || keysym == XK_d)
		; //right
	if (keysym == XK_W || keysym == XK_w)
		; //up
	if (keysym == XK_S || keysym == XK_s)
		; //down */
	return (0);
}