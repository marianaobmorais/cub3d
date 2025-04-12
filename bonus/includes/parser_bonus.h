/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:51:46 by joneves-          #+#    #+#             */
/*   Updated: 2025/04/12 16:21:40 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include <stdbool.h>

typedef struct s_cub		t_cub;
typedef struct s_sprite		t_sprite;
typedef struct s_door		t_door;

typedef enum e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}	t_directions;

typedef enum e_parser_status
{
	ERROR,
	BUFFER,
	NO_BUFFER
}	t_parser_status;

typedef struct s_map
{
	char			**matrix;
	char			**matrix_tmp;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	unsigned char	*floor_rgb;
	unsigned char	*ceiling_rgb;
	int				floor_hex;
	int				ceiling_hex;
	int				player_squ_x;
	int				player_squ_y;
	int				width;
	int				height;
	int				sprite_count;
	int				sprite_increment;
	int				door_count;
	int				door_increment;
	t_sprite		*sprite;
	t_door			*door;
	t_directions	direction;
}	t_map;

/* ft_load_map_bonus.c */

void			ft_init_map(t_cub *cub);
bool			ft_access(char *filepath);
bool			ft_is_ext(char *filename, char *ext);
void			ft_clean_map(t_cub *cub, t_map *map);
void			ft_load_map(char *const filepath, t_cub *cub);

/* ft_map_parser_bonus.c */

void			ft_map_parser(int fd, t_cub *cub, int i);

/* ft_map_parser_utils_bonus.c */

char			*ft_buffer(char *buffer, char *line, int start, t_cub *cub);
t_parser_status	ft_add_texture(char *line, t_cub *game, char *identifier, \
	t_directions direction);
char			**ft_safe_split(char *buffer, t_cub *cub);

/* ft_map_parser_utils_bonus_2.c */

bool			is_valid_sprite(char *line, char *previous_line, int x);
void			ft_count_sprites(t_cub *cub, char *line);
void			ft_set_sprite(t_cub *cub, int x, int y);
void			ft_set_door(t_cub *cub, int x, int y);
void			ft_count_doors(t_cub *cub, char *line);

/* parser_utils_bonus.c */

bool			ft_is_player(char c);
int				ft_isspace(int c, int mode);
char			*ft_strip(char *str, int mode);
int				ft_isnumeric(char *nbr);
void			ft_print_map(t_map *map); //debug

/* ft_fill_matrix_bonus.c */

void			ft_fill_matrix(t_cub *cub);

/* ft_matrix_parser_bonus.c */

void			ft_matrix_parser(t_cub *cub, char **matrix);

/* ft_matrix_parser_utils_bonus.c */

int				ft_arraytohex(unsigned char *rgb);
int				ft_is_empty(char *line);
bool			ft_valid_wall(char *line, char *previous_line, \
	bool first_or_last);

#endif //PARSER_BONUS_H