/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:33:21 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/08 11:09:17 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	lens;

	lens = ft_strlen(s);
	while (lens-- && *s != (unsigned char)c)
	{
		s++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		return ((char *)(s));
	else
		return (NULL);
}
