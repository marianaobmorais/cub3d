# include "../includes/cub3D.h"

void	ft_handle_error(const char *error_msg)
{
	//TODO insert brief
	printf("Error\n"); //stdout or stderr ?
	if (error_msg)
		printf("%s\n", error_msg);
	else
		perror("");
}
