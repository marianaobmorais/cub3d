NAME = cub3D
#B_NAME = cub3D_bonus

SRCS_DIR = ./srcs
#BONUS_DIR = ./bonus

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

MLIBX = ./minilibx-linux/libmlx.a
MLIBX_DIR = ./minilibx-linux

SRCS = $(SRCS_DIR)/main.c \
	$(SRCS_DIR)/ft_put_image.c \
	$(SRCS_DIR)/hook_utils.c \
	$(SRCS_DIR)/ft_handle_error.c \
	$(SRCS_DIR)/pixel_utils.c \
	$(SRCS_DIR)/ft_clean_game.c \
	$(SRCS_DIR)/ft_init_structs.c \
	$(SRCS_DIR)/move_utils.c \
	$(SRCS_DIR)/parser/ft_load_map.c \
	$(SRCS_DIR)/parser/ft_fill_matrix.c \
	$(SRCS_DIR)/parser/ft_map_parser.c \
	$(SRCS_DIR)/parser/ft_map_parser_utils.c \
	$(SRCS_DIR)/parser/ft_matrix_parser.c \
	$(SRCS_DIR)/parser/ft_matrix_parser_utils.c \
	$(SRCS_DIR)/parser/parser_utils.c \
	$(SRCS_DIR)/raycasting/ft_init_raycast.c \
	$(SRCS_DIR)/raycasting/ft_render_walls.c \
	$(SRCS_DIR)/raycasting/ft_paint_ray.c \
	$(SRCS_DIR)/raycasting/ft_dda.c \
	$(SRCS_DIR)/hud/ft_paint_minimap_on_hud.c \
	$(SRCS_DIR)/hud/ft_init_hud.c \
	$(SRCS_DIR)/hud/ft_paint_minimap_utils.c \
	$(SRCS_DIR)/hud/ft_put_hud.c \
	$(SRCS_DIR)/hud/screens.c \
	$(SRCS_DIR)/hud/stuffs.c \


#B_SRCS = $(BONUS_DIR)/main_bonus.c \

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
MLXFLAGS = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm -lz

RM = rm -f

$(NAME): $(LIBFT) $(MLIBX) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

all: $(NAME)
#bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
$(MLIBX):
	$(MAKE) -C $(MLIBX_DIR)

#bonus: $(B_NAME)

#$(B_NAME): $(LIBFT) $(MLIBX) $(B_SRCS)
#	$(CC) $(CFLAGS) $(B_SRCS) $(LIBFT) $(MLXFLAGS) -o $(B_NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLIBX_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(MLIBX)
	$(MAKE) fclean -C $(LIBFT_DIR)
#$(B_NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
