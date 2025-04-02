NAME = cub3D
B_NAME = cub3D_bonus

SRCS_DIR = ./mandatory/srcs
BONUS_DIR = ./bonus/srcs

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

MLIBX = ./minilibx-linux/libmlx.a
MLIBX_DIR = ./minilibx-linux

SRCS = $(SRCS_DIR)/main.c \
	$(SRCS_DIR)/ft_handle_img.c \
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

B_SRCS = $(BONUS_DIR)/main_bonus.c \
	$(BONUS_DIR)/ft_handle_img_bonus.c \
	$(BONUS_DIR)/hook_utils_bonus.c \
	$(BONUS_DIR)/hook_mouse_bonus.c \
	$(BONUS_DIR)/ft_handle_error_bonus.c \
	$(BONUS_DIR)/pixel_utils_bonus.c \
	$(BONUS_DIR)/ft_clean_game_bonus.c \
	$(BONUS_DIR)/ft_init_structs_bonus.c \
	$(BONUS_DIR)/move_utils_bonus.c \
	$(BONUS_DIR)/parser/ft_load_map_bonus.c \
	$(BONUS_DIR)/parser/ft_fill_matrix_bonus.c \
	$(BONUS_DIR)/parser/ft_map_parser_bonus.c \
	$(BONUS_DIR)/parser/ft_map_parser_utils_bonus.c \
	$(BONUS_DIR)/parser/ft_matrix_parser_bonus.c \
	$(BONUS_DIR)/parser/ft_matrix_parser_utils_bonus.c \
	$(BONUS_DIR)/parser/ft_matrix_parser_utils_2_bonus.c \
	$(BONUS_DIR)/parser/parser_utils_bonus.c \
	$(BONUS_DIR)/raycasting/ft_init_raycast_bonus.c \
	$(BONUS_DIR)/raycasting/ft_render_walls_bonus.c \
	$(BONUS_DIR)/raycasting/ft_render_sprites_bonus.c \
	$(BONUS_DIR)/raycasting/ft_paint_ray_bonus.c \
	$(BONUS_DIR)/raycasting/ft_dda_bonus.c \
	$(BONUS_DIR)/hud/ft_render_minimap_on_hud_bonus.c \
	$(BONUS_DIR)/hud/ft_render_fov_minimap_bonus.c \
	$(BONUS_DIR)/hud/ft_init_hud_bonus.c \
	$(BONUS_DIR)/hud/ft_render_minimap_utils_bonus.c \
	$(BONUS_DIR)/hud/ft_render_source_on_hud_bonus.c \
	$(BONUS_DIR)/hud/ft_render_action_bonus.c \
	$(BONUS_DIR)/hud/ft_render_viewmodel_bonus.c \
	$(BONUS_DIR)/hud/screens_bonus.c \
	$(BONUS_DIR)/hud/colors_utils_bonus.c \


CC = cc
CFLAGS = -Wall -Werror -Wextra -g
MLXFLAGS = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm -lz

RM = rm -f

$(NAME): $(LIBFT) $(MLIBX) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

all: $(NAME) bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
$(MLIBX):
	$(MAKE) -C $(MLIBX_DIR)

bonus: $(B_NAME)

$(B_NAME): $(LIBFT) $(MLIBX) $(B_SRCS)
	$(CC) $(CFLAGS) $(B_SRCS) $(LIBFT) $(MLXFLAGS) -o $(B_NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLIBX_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(MLIBX) $(B_NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
