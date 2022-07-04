/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:12 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(int i, int j)
{
	g_.i = 0;
	g_.t = 0;
	if (g_.input[0] == '|')
		return (0);
	while (g_.input[i])
	{
		if (g_.input[i] != '|' && g_.input[i] != ' ')
			j = 0;
		if (g_.input[i] == '|' && j == 0)
		{
			g_.i ++;
			j = 1;
		}
		else if ((g_.input[i] == '|' && j == 1 && g_.input[i - 1] != '|')
			|| (g_.input[i] == '|' && j == 1
				&& g_.input[i - 1] == '|' && g_.input[i - 2] == '|'))
			return (0);
		else if (g_.input[i] == '|' && j == 1 && g_.input[i - 1] == '|')
			if (!g_.t)
				g_.t = g_.i;
		i++;
	}
	if (!g_.input[i] && j == 1)
		return (0);
	return (1);
}

void	ft_pipe(int r, int t)
{
	int	i;

	i = 0;
	while (g_.s_cmd[i + 1] != 0 && t != 1 && (i + 1) != t)
	{
		r = red(g_.s_cmd[i]);
		if (r == -1)
			break ;
		else if (r)
			red_send(g_.s_cmd[i], 1, 0, 0);
		else
			exec_v2(esp_splt(g_.s_cmd[i]));
		i ++;
	}
	r = red(g_.s_cmd[i]);
	if (r && r != -1)
		red_send(g_.s_cmd[i], 0, 0, 0);
	else if (r != -1)
		exec(esp_splt(g_.s_cmd[i]));
	dup2(g_.i_stdin, 0);
	dup2(g_.i_stdout, 1);
	g_.pip = 0;
}
