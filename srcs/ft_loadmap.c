# include "../includes/cub3D.h"

bool	ft_is_cub(char *const filename)
{
	//TODO insert brief
	char	*extension;

	extension = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (!extension || ft_strlen(extension) != 4)
	{
		ft_handle_error("File extension");
		return (false);
	}
	return (true);
}

int	ft_loadmap(char *const filepath)
{
	if (ft_is_cub(filepath))
		return (1);
	return (0);
}