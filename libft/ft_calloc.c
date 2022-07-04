/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:16:44 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/07/04 21:12:18 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*cal;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	cal = (char *)malloc(size * (count + 1));
	if (!cal)
		return (NULL);
	ft_bzero(cal, (count * size));
	return (cal);
}
