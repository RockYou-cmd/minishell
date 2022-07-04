/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:14 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:28:47 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_herdoc(char *limeter)
{
	char	*doc;

	g_.pid_ch = fork();
	if (!g_.pid_ch)
	{
		doc = get_next_line(0);
		while (doc && !ft_strcmp(limeter, doc))
		{
			if (ft_strchr(limeter, '\'') || ft_strchr(limeter, '\"'))
				write(g_.fd_stdin, doc, ft_strlen(doc));
			else
				write(g_.fd_stdin, rm(doc), ft_strlen(rm(doc)));
			free(doc);
			write(g_.fd_stdin, "\n", 1);
			doc = get_next_line(0);
		}
		if (!doc)
			printf("\n");
		free(doc);
		exit(0);
	}
}

void	exec_heredoc(char *limeter)
{
	dup2(g_.i_stdout, 1);
	dup2(g_.i_stdin, 0);
	if (g_.fd_stdin != -1 && g_.fd_stdout != -1)
		g_.fd_stdin = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_herdoc(limeter);
	waitpid(g_.pid_ch, &g_.state, 0);
	if (WIFEXITED(g_.state))
		g_.state = WEXITSTATUS(g_.state);
	if (g_.state == 2)
		printf("\n");
	if (g_.fd_stdin != -1 && g_.fd_stdout != -1 && g_.state != 2)
	{
		close(g_.fd_stdin);
		g_.fd_stdin = open("/tmp/.heredoc", O_RDWR, 0644);
	}
}

void	exec_red_output(char *file, int *output)
{
	if (g_.fd_stdin == -1 || g_.fd_stdout == -1)
		return ;
	if (g_.fd_stdout != 1)
		close(g_.fd_stdout);
	*output = 1;
	g_.fd_stdout = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	exec_red_output_append(char *file, int *output)
{
	if (g_.fd_stdin == -1 || g_.fd_stdout == -1)
		return ;
	if (g_.fd_stdout != 1)
		close(g_.fd_stdout);
	*output = 1;
	g_.fd_stdout = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
}

void	exec_red_input(char *file)
{
	if (g_.fd_stdin == -1 || g_.fd_stdout == -1)
		return ;
	if (g_.fd_stdin != 0)
		close(g_.fd_stdin);
	g_.fd_stdin = open(file, O_RDWR, 0644);
	if (g_.fd_stdin == -1)
	{
		g_.file = file;
		return ;
	}
}
