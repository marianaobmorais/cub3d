
#include "../includes/cub3d.h"

void	ft_init_texture(t_cub *cub)
{
	t_raycast	*ray;

	ray = cub->raycast;
	ft_memset(&ray->north_texture, 0, sizeof(t_texture));
	ft_memset(&ray->south_texture, 0, sizeof(t_texture));
	ft_memset(&ray->east_texture, 0, sizeof(t_texture));
	ft_memset(&ray->west_texture, 0, sizeof(t_texture));
	ray->north_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
		cub->map->north_texture, &ray->north_texture.width, &ray->north_texture.height);
	ray->south_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
		cub->map->south_texture, &ray->south_texture.width, &ray->south_texture.height);
	ray->east_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
		cub->map->east_texture, &ray->east_texture.width, &ray->east_texture.height);
	ray->west_texture.img_ptr = mlx_xpm_file_to_image(cub->mlx,
		cub->map->west_texture, &ray->west_texture.width, &ray->west_texture.height);
	if (!ray->north_texture.img_ptr || !ray->south_texture.img_ptr
		|| !ray->east_texture.img_ptr || !ray->west_texture.img_ptr)
		ft_handle_error("texture.img_ptr", cub); //test this later
	ray->north_texture.addr = mlx_get_data_addr(ray->north_texture.img_ptr,
		&ray->north_texture.bpp, &ray->north_texture.line_len, &ray->north_texture.endian);
	ray->south_texture.addr = mlx_get_data_addr(ray->south_texture.img_ptr,
		&ray->south_texture.bpp, &ray->south_texture.line_len, &ray->south_texture.endian);
	ray->east_texture.addr = mlx_get_data_addr(ray->east_texture.img_ptr,
		&ray->east_texture.bpp, &ray->east_texture.line_len, &ray->east_texture.endian);
	ray->west_texture.addr = mlx_get_data_addr(ray->west_texture.img_ptr,
		&ray->west_texture.bpp, &ray->west_texture.line_len, &ray->west_texture.endian);
	if (!ray->north_texture.addr || !ray->south_texture.addr
		|| !ray->east_texture.addr || !ray->west_texture.addr)
		ft_handle_error("texture.addr", cub); //test this later
}

void	ft_init_image(t_cub *cub)
{
	cub->image = (t_image *)malloc(sizeof(t_image));
	if (!cub->image)
		ft_handle_error("malloc: cub->image", cub);
	ft_memset(cub->image, 0, sizeof(t_image));
	cub->image->img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->image->img_ptr)
		ft_handle_error("malloc: cub->image->img_ptr", cub);
	cub->image->addr = mlx_get_data_addr(cub->image->img_ptr, &cub->image->bpp,
		&cub->image->line_len, &cub->image->endian);
	if (!cub->image->addr)
		ft_handle_error("cub->image->addr", cub);
}

t_cub	*ft_init_structs(t_cub *cub, char *argv)
{
	cub = (t_cub *) malloc(sizeof(t_cub));
	if (!cub)
		ft_handle_error("malloc: cub", cub);
	ft_memset(cub, 0, sizeof(t_cub));
	ft_load_map(argv, cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_handle_error("malloc: cub->mlx", cub);
	ft_init_image(cub);
	ft_init_raycast(cub);
	ft_init_texture(cub);
	cub->window = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->window)
		ft_handle_error("malloc: cub->window", cub);
	return (cub);
}
