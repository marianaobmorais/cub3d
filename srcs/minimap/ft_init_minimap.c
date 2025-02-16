#include "../../includes/minimap.h"

void	ft_init_minimap(t_cub *cub)
{
	cub->mini = (t_minimap *) malloc(sizeof(t_minimap));
	if (!cub->mini)
		ft_handle_error("malloc: cub->mini", cub);
	cub->mini->img_minimap = (t_image *)malloc(sizeof(t_image));
	if (!cub->mini->img_minimap)
		ft_handle_error("malloc: cub->mini->img_minimap", cub);
	cub->mini->img_minimap->img_ptr = NULL;
}
