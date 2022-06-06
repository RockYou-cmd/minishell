/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:30:36 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/15 12:04:20 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	size_t	i;
	size_t	f;
	size_t	n;

	str = (char *)haystack;
	if (needle[0] == '\0' || haystack == needle)
		return (str);
	n = ft_strlen(needle);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		f = 0;
		while (needle[f] && str[i + f] && i + f < len
			&& str[i + f] == needle[f])
			f++;
		if (f == n)
			return (str + i);
		i++;
	}
	return (NULL);
}
