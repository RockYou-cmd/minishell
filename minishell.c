// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:06:09 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/05/18 17:35:55 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signm)
{
	if (signm == SIGINT && !g.pid_ch)
		exit (1);
	else if (signm == SIGINT && g.pid_ch == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signm == SIGQUIT)
		return ;
}

void	ft_read_line(void)
{
	g.input = readline("minishell-3.2$ ");
	if (!g.input)
	{
		if (g.env)
			write(1, "\033[1A\033[15Cexit\n", 14);
		else
			write(1, " exit\n", 6);
		ft_free(g.env);
		exit(1);
	}
}

void	shlvl(void)
{
	char	*v;
	char	*s;
	int		k;
	int		i;

	v = 0;
	i = 0;
	k = 0;
	while (g.env[i])
	{
		if (!strncmp(g.env[i], "SHLVL=", 6))
		{
			v = ft_strchr(g.env[i], '=');
			++v;
			k = ft_atoi(v) + 1;
			if (k < 0)
				k = 0;
			free(g.env[i]);
			s = ft_itoa(k);
			g.env[i] = ft_strjoin(ft_strdup("SHLVL="), s);
			free(s);
		}
		i++;
	}
}

void	build_env(char **env)
{
	int i;

	i = 0;
	if (!env[0])
	{
		g.env = NULL;
		return ;
	}
	while (env[i])
		i++;
	g.env = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
		g.env[i] = ft_strdup(env[i]);
	g.env[i] = 0;
	shlvl();
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	build_env(env);
	g.cmnd = -1;
	g.state = 0;
	rl_catch_signals = 0;
	g.i_stdin = dup(0);
	g.i_stdout = dup(1);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	comands();
	while (1)
	{
		g.pid_ch = 1;
		ft_read_line();
		add_history(g.input);
		g.fd_stdin = 0;
		g.fd_stdout = 1;
		g.i = 0;
		if (!ft_init())
			continue ;
		check();
		g.cmnd = -1;
	}
}
