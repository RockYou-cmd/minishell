/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:15 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/08 11:11:30 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	while (len-- && *s != c)
		s--;
	if (*s == (unsigned char)c)
		return ((char *)(s));
	else
		return (NULL);
}
