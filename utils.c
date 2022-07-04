/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:22 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/03 18:43:23 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_realloc(char **str, int t)
{
	int		i;
	char	**ret;

	i = 0;
	while (str[i])
		i ++;
	ret = ft_calloc((i + t + 1), sizeof(char *));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i ++;
	}
	ret[i] = 0;
	ft_free(str);
	return (ret);
}

char	*ft_rrealloc(char *str, int t)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
		i ++;
	ret = ft_calloc((i + t + 1), sizeof(char *));
	t += i;
	i = 0;
	while (i < t && str[i])
	{
		ret[i] = str[i];
		i ++;
	}
	ret[i] = 0;
	free(str);
	return (ret);
}

void	exit_status(void)
{
	if (g.state == 0)
		g.state = 0;
	else if (g.state == 2)
		g.state = 130;
	else if (g.state == 256)
		g.state = 127;
	else if (g.state == 512)
		g.state = 2;
}

int	no_arguments(char *str)
{
	if (str)
	{
		if (str[0] == '-' && ((str[1] != '\0' && str[1] != '-') \
			|| (str[1] == '-' && str[2] != '\0')))
		{
			printf("minishell: pwd: %s: invalid option\n", str);
			return (1);
		}
	}
	return (0);
}