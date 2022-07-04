/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:42:37 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/03 18:42:38 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_expend(char *str, int s)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	g.clr_cmd = ft_rrealloc(g.clr_cmd, ft_strlen(str));
	while (str[p] != '\0')
		g.clr_cmd[s ++] = str[p ++];
	return (s);
}

int	dolar(char *str, int s)
{
	int		i;
	int		p;
	char	*tmp2;

	i = 0;
	p = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != 0
			&& str[i + 1] != '\"' && str[i + 1] != '\''
			&& (str[i + 2] != ' ' || str[i + 2] != '\0'))
		{
			tmp2 = v_env(str + i);
			if (tmp2)
				while (tmp2[p] != '\0')
					g.clr_cmd[s ++] = tmp2[p ++];
			i += g.t + 1;
			p = 0;
			free(tmp2);
		}
		else
			g.clr_cmd[s ++] = str[i ++];
	}
	return (s);
}

int	dolar2(char *str, int s, int p, char *tmp2)
{
	char	**tmp;

	while (str[g.i] != '\"' && str[g.i] != '\'' && str[g.i] != '\0')
	{
		if (str[g.i] == '$' && str[g.i + 1] != ' ' && str[g.i + 1]
			&& str[g.i + 1] != '\"' && (str[g.i + 2] != ' ' || str[g.i + 2]))
		{
			tmp = ft_split(str + g.i, ' ');
			tmp2 = v_env(tmp[0]);
			if (tmp2)
				s = fill_expend(tmp2, s);
			ft_free(tmp);
			free(tmp2);
			g.i += g.t + 1;
			p = 0;
		}
		else if ((str[g.i] == '$' && (str[g.i + 1] == '\''
					|| str[g.i + 1] == '\"') && str[g.i + 1] != 0)
			|| (str[g.i] == ' ' && str[g.i + 1] == ' '))
			g.i ++;
		else
			g.clr_cmd[s ++] = str[g.i ++];
	}
	return (s);
}