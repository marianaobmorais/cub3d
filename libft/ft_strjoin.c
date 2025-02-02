/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:45:16 by mariaoli          #+#    #+#             */
/*   Updated: 2025/02/02 16:52:22 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*res;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		res[i] = s1[i];
		++i;
	}
	i = 0;
	while (i < l2)
	{
		res[l1 + i] = s2[i];
		++i;
	}
	res[l1 + i] = '\0';
	return (res);
}
