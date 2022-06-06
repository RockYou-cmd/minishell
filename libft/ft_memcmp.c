/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:30:53 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/08 13:20:41 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*((unsigned char *)s1 + i) == *((unsigned char *)s2 + i)
		&& (i < n - 1))
		i++;
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}
