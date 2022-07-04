/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:09 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 22:43:58 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	which_one(char **str)
{
	g_.state = 0;
	if (g_.cmnd == 0)
		g_.state = ft_echo(str, 0, 0, 0);
	if (g_.cmnd == 1)
		g_.state = ft_cd(str);
	if (g_.cmnd == 2)
		g_.state = ft_pwd(str);
	if (g_.cmnd == 3)
		g_.state = ft_export(str, 0, 0);
	if (g_.cmnd == 4)
		g_.state = ft_unset(str, 0, 0);
	if (g_.cmnd == 5)
		g_.state = ft_env(str);
	if (g_.cmnd == 6)
		ft_exit(str);
}

int	squotes(int s, char *str)
{
	int	t;

	t = 0;
	t = ++g_.i;
	while (str[g_.i] != '\'' && str[g_.i] != 0)
		g_.i++;
	if (str[g_.i] == '\'')
		while (str[t] != '\'')
			g_.clr_cmd[s++] = str[t++];
	return (s);
}

int	dquotes(int s, char *str)
{
	int	t;

	t = 0;
	t = ++g_.i;
	while (str[g_.i] != '\"' && str[g_.i] != 0)
		g_.i++;
	if (str[g_.i] == '\"')
		s = dolar(str + t, s);
	return (s);
}

char	*rm(char *str)
{
	int	s;

	s = 0;
	g_.i = 0;
	g_.clr_cmd = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[g_.i] != 0)
	{
		if (str[g_.i] == '\'')
			s = squotes(s, str);
		else if (str[g_.i] == '\"')
			s = dquotes(s, str);
		else if (str[g_.i] == ' ' && str[g_.i + 1] == ' ')
			;
		else
		{
			s = dolar2(str, s, 0);
			g_.i --;
		}
		g_.i ++;
	}
	g_.clr_cmd[s] = 0;
	g_.i = 0;
	return (g_.clr_cmd);
}

void	check(void)
{
	int	r;

	r = 0;
	if (g_.pip == 1)
		ft_pipe(r, g_.t);
	else
	{
		r = red(g_.input);
		if (r && r != -1)
			red_send(g_.input, 0, 0, 0);
		else if (r != -1)
			exec(esp_splt(g_.input));
	}
	free(g_.input);
	ft_free(g_.s_cmd);
	exit_status();
}
