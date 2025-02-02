/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:40:41 by mariaoli          #+#    #+#             */
/*   Updated: 2025/02/02 16:50:34 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	size_t	totalsize;
	void	*ptr;

	totalsize = number * size;
	ptr = (void *)malloc(totalsize);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, totalsize);
	return (ptr);
}
