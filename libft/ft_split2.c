/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:48:18 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/07/04 20:52:43 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c )
{
	int	i;
	int	w;
	int	d;
	int	sq;

	i = 0;
	w = 0;
	d = 0;
	sq = 0;
	while (s[i])
	{
		cote(&d, &sq, s[i]);
		if (s[i] != c && (s[i + 1] == c
				|| s[i + 1] == '\0') && sq == 0 && d == 0)
			w++;
		i++;
	}
	if (d || sq)
	{
		printf("minishell: syntax error\n");
		return (-1);
	}
	return (w);
}

static int	len(char const *s, char c)
{
	int	i;
	int	d;
	int	sq;

	d = 0;
	sq = 0;
	i = 0;
	while (s[i])
	{
		cote(&d, &sq, s[i]);
		if (s[i] == c && (sq == 0 && d == 0))
			break ;
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
	t_var	v;

	v.d = 0;
	v.sq = 0;
	v.i = -1;
	while (++v.i < w)
	{	
		while (c == *s && v.sq == 0 && v.d == 0)
		{
			cote(&v.d, &v.sq, *s);
			s ++;
		}
		v.l = len(s, c);
		split[v.i] = (char *)malloc(sizeof(char) * v.l + 1);
		if (!split[v.i])
			leak(split, v.i);
		v.j = 0;
		while (v.j < v.l)
		{
			cote(&v.d, &v.sq, *s);
			split[v.i][v.j++] = *s++;
		}
		cote(&v.d, &v.sq, *s);
		split[v.i][v.j] = '\0';
	}
}

char	**ft_split(char const *s, char c)
{
	int		w;
	char	**split;

	if (!s)
		return (NULL);
	w = count(s, c);
	if (w == -1)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (w + 1));
	if (!split)
		return (NULL);
	write_sp(split, s, c, w);
	split[w] = 0;
	return (split);
}
