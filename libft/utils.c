/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:54:26 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 20:54:27 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cote(int *d, int *sq, char c)
{
	if (c == '\"' && *sq == 0)
	{
		if (*d == 0)
			*d = 1;
		else
			*d = 0;
	}
	else if (c == '\'' && *d == 0)
	{
		if (*sq == 0)
			*sq = 1;
		else
			*sq = 0;
	}
}
