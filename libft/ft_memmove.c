/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaoli <mariaoli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:17:15 by mariaoli          #+#    #+#             */
/*   Updated: 2025/02/02 16:51:29 by mariaoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cdst;
	const char	*csrc;

	cdst = (char *)dst;
	csrc = (const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src > dst)
	{
		ft_memcpy(cdst, csrc, len);
		return (cdst);
	}
	if (src < dst)
	{
		while (len > 0)
		{
			len--;
			cdst[len] = csrc[len];
		}
	}
	return (cdst);
}
