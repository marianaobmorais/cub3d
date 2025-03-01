#include "../../includes/minimap.h"

int	ft_get_pixel_color(t_cub *cub, int x, int y, t_image *texture)
{
	char	*addr;
	char	*dst;
	int		offset;
	(void)cub;

	addr = texture->addr ;//mlx_get_data_addr(texture, &texture->bpp, &texture->line_len, &texture->endian);
	offset = (y * texture->line_len) + (x * (texture->bpp / 8));

	//addr = mlx_get_data_addr(cub->mini->img_texture, &cub->mini->img_minimap->bpp, &cub->mini->img_minimap->line_len, &cub->mini->img_minimap->endian);
	// offset = (y * cub->mini->img_minimap->line_len) + (x * (cub->mini->img_minimap->bpp / 8));
	dst = offset + addr;
	return (*(unsigned int *)dst);
}

void	ft_background(t_cub *cub)
{
	int	y = 0;
	int	x;
	int	color;
	t_image img;
	t_image texture;

	int w = 120;
	int h = 125;

	img.img_ptr = mlx_new_image(cub->mlx, 120, 125);
	img.bpp = 0;
	img.endian = 0;
	img.line_len = 0;
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);

	texture.img_ptr = mlx_xpm_file_to_image(cub->mlx, "assets/textures/casio_w.xpm", &w, &h);
	texture.bpp = 0;
	texture.endian = 0;
	texture.line_len = 0;
	texture.addr = mlx_get_data_addr(texture.img_ptr, &texture.bpp, &texture.line_len, &texture.endian);

	while (y < 125)
	{
		x = 0;
		while (x < 120)
		{
			color = ft_get_pixel_color(cub, x, y, &texture);
			if (color == 0xFFFFFF)
			{
				//printf("[%d] %x\n", x, ft_get_pixel_color(cub, 0, y)); //debug
				//ft_put_pixel(&img, x, y, 0xB0CFDD);
				ft_put_pixel(&img, x, y, ft_get_pixel_color(cub, x, y, cub->image)); //test
			}
			else
				ft_put_pixel(&img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->window, img.img_ptr, 0, 0);
}
