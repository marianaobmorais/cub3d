/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:46:30 by mariaoli          #+#    #+#             */
/*   Updated: 2025/02/02 16:53:06 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	size_t	l_len;

	b = (char *)big;
	if (*little == '\0')
		return (b);
	l_len = ft_strlen(little);
	while (*b != '\0' && len > 0)
	{
		if (ft_strncmp(b, little, l_len) == 0 && l_len <= len)
			return (b);
		++b;
		--len;
	}
	return (NULL);
}
