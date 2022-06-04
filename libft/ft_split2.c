/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:48:18 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/06/04 18:54:51 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cote(int *d,int *sq, char c)
{
	if (c == '\"')
	{
		if (*d == 0)
			*d = 1;
		else
			*d = 0;
	}
	else if (c == '\'')
	{
		if (*sq == 0)
			*sq = 1;
		else
			*sq = 0;
	}
}
static int	count(char const *s, char c )
{
	int	i;
	int	w;
	int d;
	int sq;

	i = 0;
	w = 0;
	d = 0;
	sq = 0;
	while (s[i])
	{
		cote(&d, &sq, s[i]);
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0') && sq == 0 && d == 0)
			w++;
		i++;
	}
	return (w);
}

static int	len(char const *s, char c)
{
	int	i;
	int d;
	int sq;
	
	d = 0;
	sq = 0;

	i = 0;
	while (s[i])
	{
		cote(&d, &sq, s[i]);
		if (s[i] == c  && (sq == 0 && d == 0))
			break;
		i ++;

	}
	return (i);
}

static void	leak(char **split, int l)
{
	int	i;

	i = -1;
	while (++i < l)
		free(split[i]);
	free(split);
}

static void	write_sp(char **split, char const *s, char c, int w)
{
	int	i;
	int	j;
	int	l;
	int d;
	int sq;
	
	d = 0;
	sq = 0;
	i = -1;
	while (++i < w)
	{
		
		while (c == * s && sq == 0 && d == 0)
		{
			s++;
			cote(&d, &sq, *s);
		}
		l = len(s, c);
		split[i] = (char *)malloc(sizeof(char) * l + 1);
		if (!split[i])
			leak(split, i);
		j = 0;
		while (j < l)
			split[i][j++] = *s++;
		split[i][j] = '\0';
	}
}

char	**ft_split_v2(char const *s, char c)
{
	int		w;
	char	**split;

	if (!s)
		return (NULL);
	w = count(s, c);
	split = (char **)malloc(sizeof(char *) * w + 1);
	if (!split)
		return (NULL);
	write_sp(split, s, c, w);
	split[w] = 0;
	return (split);
}