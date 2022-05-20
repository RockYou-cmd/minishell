/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:48:18 by rgatnaou          #+#    #+#             */
/*   Updated: 2021/11/17 14:41:03 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			w++;
		i++;
	}
	return (w);
}

static int	len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
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

	i = -1;
	while (++i < w)
	{
		while (c == *s)
			s++;
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

char	**ft_split(char const *s, char c)
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
