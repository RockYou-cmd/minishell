/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:09 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 18:45:26 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	which_one(char **str)
{
	g.state = 0;
	if (g.cmnd == 0)
		g.state = ft_echo(str, 0, 0, 0);
	if (g.cmnd == 1)
		g.state = ft_cd(str);
	if (g.cmnd == 2)
		g.state = ft_pwd(str);
	if (g.cmnd == 3)
		g.state = ft_export(str, 0, 0);
	if (g.cmnd == 4)
		g.state = ft_unset(str);
	if (g.cmnd == 5)
		g.state = ft_env(str);
	if (g.cmnd == 6)
		ft_exit(str);
}

int	squotes(int s, char *str)
{
	int	t;

	t = 0;
	t = ++g.i;
	while (str[g.i] != '\'' && str[g.i] != 0)
		g.i++;
	if (str[g.i] == '\'')
		while (str[t] != '\'')
			g.clr_cmd[s++] = str[t++];
	return (s);
}

int	dquotes(int s, char *str)
{
	int	t;

	t = 0;
	t = ++g.i;
	while (str[g.i] != '\"' && str[g.i] != 0)
		g.i++;
	if (str[g.i] == '\"')
		s = dolar(str + t, s);
	return (s);
}

char	*rm(char *str)
{
	int	s;

	s = 0;
	g.i = 0;
	g.clr_cmd = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[g.i] != 0)
	{
		if (str[g.i] == '\'')
			s = squotes(s, str);
		else if (str[g.i] == '\"')
			s = dquotes(s, str);
		else if (str[g.i] == ' ' && str[g.i + 1] == ' ')
			;
		else
		{
			s = dolar2(str, s, 0);
			g.i --;
		}
		g.i ++;
	}
	g.clr_cmd[s] = 0;
	g.i = 0;
	return (g.clr_cmd);
}

void	check(void)
{
	int	r;

	r = 0;
	if (g.pip == 1)
		ft_pipe(r, g.t);
	else
	{
		r = red(g.input);
		if (r && r != -1)
			red_send(g.input, 0, 0, 0);
		else if (r != -1)
			exec(esp_splt(g.input));
	}
	free(g.input);
	ft_free(g.s_cmd);
	exit_status();
}
