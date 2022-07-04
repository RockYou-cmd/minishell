/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:15 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/07/04 21:19:43 by ael-korc         ###   ########.fr       */
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
