/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:00:16 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:09:53 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	char		rd[2];
	char		*res;
	int			r_rd;

	res = malloc(1);
	if (!res)
		return (NULL);
	r_rd = 1;
	res[0] = 0;
	while (!ft_strchr(res, '\n') && r_rd)
	{
		r_rd = read(fd, rd, 1);
		if (r_rd == -1 || !r_rd)
		{
			free(res);
			return (NULL);
		}
		rd[r_rd] = '\0';
		if (rd[0] == '\n')
			break ;
		res = ft_strjoin(res, rd);
	}
	return (res);
}
