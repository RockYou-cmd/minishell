/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:00:08 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/03 18:52:23 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	dst[i] = '\0';
	return (len);
}
