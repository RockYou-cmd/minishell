/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:43:13 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/11 18:43:02 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lendst;
	size_t	lensrc;
	size_t	ldst;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	ldst = lendst;
	i = 0;
	if (!dst || !src)
		return (0);
	if (lendst >= dstsize)
		return (lensrc + dstsize);
	while (ldst < dstsize - 1 && src[i])
	{
		dst[ldst] = src[i];
		i++;
		ldst++;
	}
	dst[ldst] = '\0';
	return (lensrc + lendst);
}
