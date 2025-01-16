# include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	if (argc != 2)
	{
		ft_handle_error(strerror(EINVAL));
		exit(2);
	}
	//ft_loadmap(argv);
	//printf("%s");
	printf("Starting cub3D...\n");
	return (0);
}