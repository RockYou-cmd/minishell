#include "minishell.h"

char	*get_bin(char	*cmd)
{
	int		i;
	char	*bin;
	char	*pat;

	i = -1;
	if (!cmd || !g.env)
		return (NULL);
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	while (g.env[++i])
		if (!ft_strncmp(g.env[i], "PATH=", 5))
			g.path = ft_split(g.env[i] + 5, ':');
	i = 0;
	while (g.path[i])
	{
		pat = ft_strdup(g.path[i]);
		pat = ft_strjoin(pat, "/");
		bin = ft_strjoin(pat, cmd);
		if (!access(bin, X_OK))
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

int	check_build_command(char **cmd)
{
	int	t;

	t = 0;
	g.cmnd = -1;
	while (g.command[t] != 0)
	{
		if (ft_strcmp(cmd[0], g.command[t]))
		{
			g.cmnd = t;
			which_one(&cmd[1]);
			ft_free(cmd);
			return (1);
		}
		t++;
	}
	return (0);
}

void	ft_execve(char *bin, char **s_cmd, int pipe)
{
	int	check;

	if (pipe)
	{
		dup2(g.pipefd[1], 1);
		close(g.pipefd[1]);
		close(g.pipefd[0]);
		check = check_build_command(s_cmd);
		if (check)
			exit(1);
	}
	execve(bin, s_cmd, g.env);
	write(2, "minishell :", 11);
	write(2, s_cmd[0], ft_strlen(s_cmd[0]));
	write(2, ": command not found\n", 20);
	exit(1);
}

void	exec(char	**s_cmd)
{
	int		check;
	char	*bin;

	if (!s_cmd || !s_cmd [0])
		return ;
	check = check_build_command(s_cmd);
	if (check)
		return ;
	bin = get_bin(s_cmd[0]);
	g.pid_ch = fork();
	if (!g.pid_ch)
	{
		signal(SIGINT, &handler);
		ft_execve(bin, s_cmd, 0);
	}
	// ft_free(s_cmd);
	free(bin);
	waitpid(g.pid_ch, &(g.state), 0);
	g.pid_ch = 1337;
}

void	exec_v2(char	**s_cmd)
{
	char	*bin;

	if (!s_cmd || !s_cmd[0])
		return ;
	pipe(g.pipefd);
	bin = get_bin(s_cmd[0]);
	g.pid_ch = fork();
	if (!g.pid_ch)
	{
		dup2(g.pipefd[1], 1);
		close(g.pipefd[1]);
		close(g.pipefd[0]);
		ft_execve(bin, s_cmd, 1);
	}
	// ft_free(s_cmd);
	free(bin);
	dup2(g.pipefd[0], 0);
	close(g.pipefd[1]);
	close(g.pipefd[0]);
}
