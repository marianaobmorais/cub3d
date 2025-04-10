/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:26:59 by mariaoli          #+#    #+#             */
/*   Updated: 2025/04/10 14:19:09 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_BONUS_H
# define IMAGE_BONUS_H

/* measurements */

# define WIDTH 960
# define HEIGHT 600

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_ipoint;

typedef enum e_door_status
{
	CLOSED,
	OPEN,
	OPENING,
	CLOSING
}	t_door_status;

#endif //IMAGE_BONUS_H
