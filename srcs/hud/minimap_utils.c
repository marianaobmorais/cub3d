#include "../../includes/hud.h"

// char	**ft_matrixdup(char **matrix, t_cub *cub)
// {
// 	int		i;
// 	char	**dup;

// 	i = 0;
// 	dup = NULL;
// 	while (matrix[i])
// 		i++;
// 	dup = (char **) malloc(i * sizeof(char *));
// 	if (!dup)
// 		ft_handle_error("malloc: matrixdup", cub);
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		dup[i] = ft_strdup(matrix[i]);
// 		i++;
// 	}
// 	dup[i] = NULL;
// 	return (dup);
// }

void	ft_put_square(t_image *img, int x, int y, int color)
{
	//add brief
	int	offset;
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 5;
	x *= size;
	y *= size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == 0 || i == size - 1 || j == 0 || j == size - 1 ||
				(i == 1 && (j == 1 || j == size - 2)) ||
				(i == size - 2 && (j == 1 || j == size - 2)))
			{
				offset = ((y + i) * img->line_len) + ((x  + j) * (img->bpp / 8));
				*((unsigned int *)(offset + img->addr)) = color;
			}
			j++;
		}
		i++;
	}
}

void	ft_set_limit_x(t_cub *cub, int matrix_width)
{
	cub->mini->start_x = cub->map->player_pos_x - 8;
	cub->mini->end_x = cub->map->player_pos_x + 8;
	if (cub->mini->start_x < 0)
	{
		cub->mini->end_x -= cub->mini->start_x;
		cub->mini->start_x = 0;
	}
	if (cub->mini->end_x >= matrix_width)
	{
		cub->mini->start_x -= (cub->mini->end_x - matrix_width + 1);
		if (cub->mini->start_x < 0)
			cub->mini->start_x = 0;
		cub->mini->end_x = matrix_width - 1;
	}
}

void	ft_set_limit_y(t_cub *cub, int matrix_height)
{
	cub->mini->start_y = cub->map->player_pos_y - 5;
	cub->mini->end_y = cub->map->player_pos_y + 5;
	if (cub->mini->start_y < 0)
	{
		cub->mini->end_y -= cub->mini->start_y;
		cub->mini->start_y = 0;
	}
	if (cub->mini->end_y >= matrix_height)
	{
		cub->mini->start_y -= (cub->mini->end_y - matrix_height + 1);
		if (cub->mini->start_y < 0)
			cub->mini->start_y = 0;
		cub->mini->end_y = matrix_height - 1;
	}
}
