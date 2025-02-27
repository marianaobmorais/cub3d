
#include "../includes/cub3d.h"

t_cub	*ft_init_structs(t_cub *cub)
{
	//add the other inits here?
	cub = (t_cub *) malloc(sizeof(t_cub));
	if (!cub)
		ft_handle_error("malloc: cub", cub);
	cub->mlx = NULL;
	cub->window = NULL;
	cub->image = NULL;
	cub->minimap = NULL;
	cub->raycast = NULL;
	//ft_init_raycast(cub);
	return (cub);
}
