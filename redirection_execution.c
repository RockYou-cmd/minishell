/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:14 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 15:46:19 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_herdoc(char *limeter)
{
	char	*doc;

	g.pid_ch = fork();
	g.sig = -1;
	if (!g.pid_ch)
	{
		doc	= get_next_line(0);
		while (doc && !ft_strcmp(limeter, doc))
		{
			if (ft_strchr(limeter, '\'') || ft_strchr(limeter, '\"'))
				write(g.fd_stdin, doc, ft_strlen(doc));
			else
				write(g.fd_stdin, rm(doc), ft_strlen(rm(doc)));
			free(doc);
			write(g.fd_stdin, "\n", 1);
			doc = get_next_line(0);
		}
		if (!doc)
			printf("\n");
		free(doc);
		exit(0);
	}
	waitpid(g.pid_ch, &g.state, 0);
	if (WIFEXITED(g.state))
		g.state = WEXITSTATUS(g.state);
	if (g.state == 2)
		printf("\n");
}

void	exec_heredoc(char *limeter)
{
	dup2(g.i_stdout, 1);
	dup2(g.i_stdin, 0);
	if (g.fd_stdin != -1 && g.fd_stdout != -1)
		g.fd_stdin = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_herdoc(limeter);
	if (g.fd_stdin != -1 && g.fd_stdout != -1 && g.state != 2)
	{
		close(g.fd_stdin);
		g.fd_stdin = open("/tmp/.heredoc", O_RDWR, 0644);
	}
}

void	exec_red_output(char *file, int *output)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return ;
	if (g.fd_stdout != 1)
		close(g.fd_stdout);
	*output = 1;
	g.fd_stdout = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	exec_red_output_append(char *file, int *output)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return ;
	if (g.fd_stdout != 1)
		close(g.fd_stdout);
	*output = 1;
	g.fd_stdout = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
}

void	exec_red_input(char *file)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return ;
	if (g.fd_stdin != 0)
		close(g.fd_stdin);
	g.fd_stdin = open(file, O_RDWR, 0644);
	if (g.fd_stdin == -1)
	{
		g.file = file;
		return ;
	}
}
