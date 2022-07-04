/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sys_Cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:19 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/03 19:54:37 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_bin(char *cmd, int i)
{
	char	*bin;
	char	**path;

	path = NULL;
	if (!g.env)
		return (NULL);
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	while (g.env[++i])
		if (!ft_strncmp(g.env[i], "PATH=", 5))
			path = ft_split(g.env[i] + 5, ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		bin = ft_strjoin(ft_strjoin(ft_strdup(path[i]), "/"), cmd);
		if (!access(bin, X_OK))
		{
			ft_free(path);
			return (bin);
		}
		free(bin);
	}
	ft_free(path);
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
	else if(g.pip)
	{
		check = check_build_command(s_cmd);
		if (check)
			exit(1);
	}
	execve(bin, s_cmd, g.env);
	write(2, "minishell :", 11);
	write(2, s_cmd[0], ft_strlen(s_cmd[0]));
	write(2, ": command not found\n", 20);
}

void	exec(char	**s_cmd)
{
	char	*bin;
	int		check;

	if (!s_cmd || !s_cmd [0])
		return ;
	if (g.pip)
		check = 0;
	else 
		check = check_build_command(s_cmd);
	if (check)
		return ;
	bin = get_bin(s_cmd[0], -1);
	g.pid_ch = fork();
	if (!g.pid_ch)
	{
		ft_execve(bin, s_cmd, 0);
		exit(1);
	}
	ft_free(s_cmd);
	free(bin);
	waitpid(g.pid_ch, &(g.state), 0);
	if (g.state == SIGINT)
		printf("\n");
	if (g.state == SIGQUIT)
		printf("Quit: 3\n");
	g.pid_ch = 1337;
}

void	exec_v2(char	**s_cmd)
{
	char	*bin;

	if (!s_cmd || !s_cmd[0])
		return ;
	pipe(g.pipefd);
	bin = get_bin(s_cmd[0], -1);
	g.pid_ch = fork();
	if (!g.pid_ch)
	{
		ft_execve(bin, s_cmd, 1);
		exit(1);
	}
	ft_free(s_cmd);
	free(bin);
	dup2(g.pipefd[0], 0);
	close(g.pipefd[1]);
	close(g.pipefd[0]);
}
