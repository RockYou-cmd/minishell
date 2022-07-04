/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:17 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 22:42:58 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ooc(char c, int *s, int *d)
{
	if (c == '\"')
	{
		if (*d == 0 && *s == 0)
			*d = 1;
		else
			*d = 0;
	}
	else if (c == '\'' && *d == 0)
	{
		if (*s == 0)
			*s = 1;
		else
			*s = 0;
	}
}

int	cmd_len(char	**str)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (str[i])
	{
		if ((ft_strcmp(str[i], "<<") || ft_strcmp(str[i], ">>")
				|| ft_strcmp(str[i], "<") || ft_strcmp(str[i], ">")))
			i ++;
		else
			l ++;
		i ++;
	}
	return (l);
}

void	ft_error(char	**cmd)
{
	dup2(g_.i_stdin, 0);
	dup2(g_.i_stdout, 1);
	close(g_.fd_stdin);
	printf("Error: no file descriptor : %s\n", g_.file);
	ft_free(cmd);
}

void	exec_red(char **cmd, int pip, int output)
{
	if (g_.fd_stdin != -1 && g_.fd_stdout != -1)
	{
		dup2(g_.fd_stdin, 0);
		dup2(g_.fd_stdout, 1);
		if (pip && !output)
			exec_v2(cmd);
		else
		{
			exec(cmd);
			if (pip && output)
			{
				pipe(g_.pipefd);
				dup2(g_.pipefd[0], 0);
				close(g_.pipefd[1]);
				close(g_.pipefd[0]);
			}
			else
				dup2(g_.i_stdin, 0);
			dup2(g_.i_stdout, 1);
		}
	}
	else
		ft_error(cmd);
	g_.fd_stdout = 1;
	g_.fd_stdin = 0;
}

void	red_send(char *str, int pip, int i, int t)
{
	char	**red;
	char	**cmd;
	char	*tmp;
	int		output;

	output = 0;
	g_.file = NULL;
	g_.fd_stdin = 0;
	g_.fd_stdout = 1;
	tmp = add_spaces(str, 0, 0);
	red = ft_split(tmp, ' ');
	free(tmp);
	cmd = malloc((cmd_len(red) + 1) * sizeof(char *));
	while (red[i])
	{
		if (ft_strcmp(red[i], "<<") || ft_strcmp(red[i], ">>")
			|| ft_strcmp(red[i], "<") || ft_strcmp(red[i], ">"))
			find_red(red, i++, &output);
		else
			cmd[t ++] = rm(red[i]);
		i++;
	}
	cmd[t] = 0;
	exec_red(cmd, pip, output);
	ft_free(red);
}
