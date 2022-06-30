
#include "minishell.h"

void	ft_herdoc(char *limeter)
{
	char	*doc;

	g.pid_ch = fork();
	if (!g.pid_ch)
	{
		signal(SIGINT, SIG_DFL);
		while (limeter)
		{
			doc = readline("> ");
			if (!doc)
			{
				write(1, "\033[1A> ", 6);
				break ;
			}
			if (ft_strcmp(limeter, doc))
				break ;
			write(g.fd_stdin, doc, ft_strlen(doc));
			write(g.fd_stdin, "\n", 1);
			free(doc);
		}
		exit(0);
	}
	waitpid(g.pid_ch, NULL, 0);
}

void	exec_heredoc(char *limeter)
{
	dup2(g.i_stdout, 1);
	dup2(g.i_stdin, 0);
	if (g.fd_stdin != -1 && g.fd_stdout != -1)
		g.fd_stdin = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_herdoc(limeter);
	g.pid_ch = 1337;
	if (g.fd_stdin != -1 && g.fd_stdout != -1)
	{
		close(g.fd_stdin);
		g.fd_stdin = open("/tmp/.heredoc", O_RDWR, 0644);
	}
}

void	exec_red_output(char *file, int *pipe)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return ;
	if (g.fd_stdout != 1)
		close(g.fd_stdout);
	*pipe = 0;
	g.fd_stdout = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	exec_red_output_append(char *file, int *pipe)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return ;
	if (g.fd_stdout != 1)
		close(g.fd_stdout);
	*pipe = 0;
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
