#include "minishell.h"


int	cmd_len(char	**str)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (str[i])
	{
		if ((ft_strcmp(str[i], "<<") || ft_strcmp(str[i], ">>")
			|| ft_strcmp(str[i], "<") || ft_strcmp(str[i], ">") ))
			i ++;
		else
			l ++;
		i ++;
	}
	return (l);
}

void	red_send(char *str, int pip)
{
	char	**red;
	char	**cmd;
	char	*tmp;
	int		i;
	int		t;
	int		output;

	i = 0;
	t = 0;
	output = 1;
	tmp = add_spaces(str);
	red = ft_split(tmp, ' ');
	free(tmp);
	cmd = malloc((cmd_len(red) + 1) * sizeof(char *));
	while (red[i])
	{
		if (ft_strcmp(red[i], "<<") || ft_strcmp(red[i], ">>") || ft_strcmp(red[i], "<") || ft_strcmp(red[i], ">"))
			find_red(red, i++, &output);
		else
			cmd[t ++] = ft_strdup(red[i]);
		i++;
	}
	cmd[t] = 0;
	if (g.fd_stdin != -1 && g.fd_stdout != -1)
	{
		dup2(g.fd_stdin, 0);
		dup2(g.fd_stdout, 1);
		if (pip && output)
			exec_v2(cmd);
		else
		{
			exec(cmd);
			if (!output && pip)
			{
				pipe(g.pipefd);
				dup2(g.pipefd[0], 0);
				close(g.pipefd[1]);
				close(g.pipefd[0]);
			}
			else
				dup2(g.i_stdin, 0);
			dup2(g.i_stdout, 1);
		}
	}
	else
	{
		dup2(g.i_stdin, 0);
		dup2(g.i_stdout, 1);
		close(g.fd_stdin);
		printf("Error: no file descriptor : %s\n", g.file);
		g.state = 1;
		ft_free(cmd);
	}
	ft_free(red);
}