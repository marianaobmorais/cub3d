/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:43:51 by mariaoli          #+#    #+#             */
/*   Updated: 2025/02/02 16:51:59 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (ft_putstr_fd("(null)", fd));
	while (s[count] != '\0')
	{
		write(fd, &s[count], sizeof(char));
		count++;
	}
	return (count);
}
