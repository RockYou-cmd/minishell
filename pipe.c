/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:12 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/03 19:07:29 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(int i, int j)
{
	g.i = 0;
	g.t = 0;
	if (g.input[0] == '|')
		return (0);
	while (g.input[i])
	{
		if (g.input[i] != '|' && g.input[i] != ' ')
			j = 0;
		if (g.input[i] == '|' && j == 0)
		{
			g.i ++;
			j = 1;
		}
		else if ((g.input[i] == '|' && j == 1 && g.input[i - 1] != '|')
			|| (g.input[i] == '|' && j == 1
				&& g.input[i - 1] == '|' && g.input[i - 2] == '|'))
			return (0);
		else if (g.input[i] == '|' && j == 1 && g.input[i - 1] == '|')
			if (!g.t)
				g.t = g.i;
		i++;
	}
	if (!g.input[i] && j == 1)
		return (0);
	return (1);
}

void	ft_pipe(int r, int t)
{
	int	i;

	i = 0;
	while (g.s_cmd[i + 1] != 0 && t != 1 && (i + 1) != t)
	{
		r = red(g.s_cmd[i]);
		if (r == -1)
			break ;
		else if (r)
			red_send(g.s_cmd[i], 1);
		else
			exec_v2(esp_splt(g.s_cmd[i]));
		i ++;
	}
	r = red(g.s_cmd[i]);
	if (r && r != -1)
		red_send(g.s_cmd[i], 0);
	else if (r != -1)
		exec(esp_splt(g.s_cmd[i]));
	dup2(g.i_stdin, 0);
	dup2(g.i_stdout, 1);
	g.pip = 0;
}