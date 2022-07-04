/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_find.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:16 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spce_ned(char	*str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' '
			&& str[i + 1] != str[i])
			len++;
		if (i > 0)
		{
			if ((str[i] == '>' || str[i] == '<') && str[i - 1] != ' '
				&& str[i - 1] != str[i])
				len ++;
		}
		i ++;
	}
	return (len);
}

char	*add_spaces(char *str, int i, int t)
{
	char	*ret;
	int		d;
	int		s;

	d = 0;
	s = 0;
	ret = malloc((spce_ned(str) + ft_strlen(str) + 1) * sizeof(char));
	while (str[i])
	{
		ooc(str[i], &s, &d);
		if (i > 0)
			if ((str[i] == '>' || str[i] == '<') && str[i - 1] != ' '
				&& str[i - 1] != str[i] && d == 0 && s == 0)
				ret[t ++] = ' ';
		ret[t ++] = str[i];
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' '
			&& str[i + 1] != str[i] && d == 0 && s == 0)
			ret[t ++] = ' ';
		i ++;
	}
	ret[t] = 0;
	return (ret);
}

int	red_check(int i, char **ptp)
{
	while (ptp[i])
	{
		if ((ft_strchr(ptp[i], '>') || ft_strchr(ptp[i], '<'))
			&& (!(ft_strchr(ptp[i], '\'')) && !(ft_strchr(ptp[i], '\"'))))
		{
			if ((ft_strcmp(ptp[i], "<<") || ft_strcmp(ptp[i], ">>")
					|| ft_strcmp(ptp[i], "<")
					|| ft_strcmp(ptp[i], ">")) && g_.t == 0)
			{
				g_.i = 1;
				g_.t = 1;
			}
			else
				return (-1);
		}
		else
			g_.t = 0;
		i ++;
	}
	if (g_.t == 1)
		return (-1);
	return (g_.i);
}

void	find_red(char **str, int i, int *output)
{
	if (ft_strcmp(str[i], "<<"))
		exec_heredoc(str[i + 1]);
	else if (ft_strcmp(str[i], ">>"))
		exec_red_output_append(rm(str[i + 1]), output);
	else if (ft_strcmp(str[i], "<"))
		exec_red_input(rm(str[i + 1]));
	else if (ft_strcmp(str[i], ">"))
		exec_red_output(rm(str[i + 1]), output);
}

int	red(char *str)
{
	char	**ptp;
	char	*tmp;

	tmp = add_spaces(str, 0, 0);
	ptp = ft_split(tmp, ' ');
	free(tmp);
	g_.i = 0;
	g_.t = 0;
	if (red_check(0, ptp) == 1)
	{
		ft_free(ptp);
		return (1);
	}
	else if (red_check(0, ptp) == -1)
	{
		ft_free(ptp);
		printf("parse error\n");
		g_.state = 258;
		return (-1);
	}
	ft_free(ptp);
	return (0);
}
