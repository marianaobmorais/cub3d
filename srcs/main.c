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
	ft_loadmap(argv[1]);
	printf("Starting cub3D...\n");
	//printf("%s");
	return (0);
}