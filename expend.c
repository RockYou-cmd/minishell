/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:42:37 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_expend(char *str, int s)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	g_.clr_cmd = ft_rrealloc(g_.clr_cmd, ft_strlen(str));
	while (str[p] != '\0')
		g_.clr_cmd[s ++] = str[p ++];
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
					s = fill_expend(tmp2, s);
			i += g_.t + 1;
			p = 0;
		}
		else
			g_.clr_cmd[s ++] = str[i ++];
	}
	return (s);
}

int	dolar2(char *str, int s, char *tmp2)
{
	char	**tmp;

	while (str[g_.i] != '\"' && str[g_.i] != '\'' && str[g_.i] != '\0')
	{
		if (str[g_.i] == '$' && str[g_.i + 1] != ' ' && str[g_.i + 1]
			&& str[g_.i + 1] != '\"' && (str[g_.i + 2] != ' ' || str[g_.i + 2]))
		{
			tmp = ft_split(str + g_.i, ' ');
			tmp2 = v_env(tmp[0]);
			if (tmp2)
				s = fill_expend(tmp2, s);
			ft_free(tmp);
			free(tmp2);
			g_.i += g_.t + 1;
		}
		else if ((str[g_.i] == '$' && (str[g_.i + 1] == '\''
					|| str[g_.i + 1] == '\"') && str[g_.i + 1] != 0)
			|| (str[g_.i] == ' ' && str[g_.i + 1] == ' '))
			g_.i ++;
		else
			g_.clr_cmd[s ++] = str[g_.i ++];
	}
	return (s);
}
