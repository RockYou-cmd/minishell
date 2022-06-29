/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:21:09 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/09 14:44:54 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1)
		&& (*((unsigned char *)s1 + i) && ((unsigned char *)s2 + i))
		&& (*((unsigned char *)s1 + i) == *((unsigned char *)s2 + i)))
		i++;
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}
