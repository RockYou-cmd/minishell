/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:16:44 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/08 18:20:21 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*cal;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	cal = (char *)malloc(size * count);
	if (!cal)
		return (NULL);
	ft_bzero(cal, (count * size));
	return (cal);
}
