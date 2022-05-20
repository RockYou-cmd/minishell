/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:14:56 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/06 12:27:47 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{	
	while (n--)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((void *)(s));
		s++;
	}
	return (NULL);
}
