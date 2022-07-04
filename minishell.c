/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:00 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signm)
{
	if (signm == SIGINT && !g_.pid_ch)
		exit (2);
	if (signm == SIGINT && g_.pid_ch == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_read_line(void)
{
	g_.input = readline("minishell-3.2$ ");
	if (!g_.input)
	{
		if (g_.env)
			write(1, "\033[1A\033[15Cexit\n", 14);
		else
			write(1, " exit\n", 6);
		ft_free(g_.env);
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
	while (g_.env[i])
	{
		if (!strncmp(g_.env[i], "SHLVL=", 6))
		{
			v = ft_strchr(g_.env[i], '=');
			++v;
			k = ft_atoi(v) + 1;
			if (k < 0)
				k = 0;
			free(g_.env[i]);
			s = ft_itoa(k);
			g_.env[i] = ft_strjoin(ft_strdup("SHLVL="), s);
			free(s);
		}
		i++;
	}
}

void	build_env(char **env)
{
	int	i;

	i = 0;
	if (!env[0])
	{
		g_.env = NULL;
		return ;
	}
	while (env[i])
		i++;
	g_.env = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
		g_.env[i] = ft_strdup(env[i]);
	g_.env[i] = 0;
	shlvl();
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	build_env(env);
	g_.cmnd = -1;
	g_.state = 0;
	rl_catch_signals = 0;
	g_.i_stdin = dup(0);
	g_.i_stdout = dup(1);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	comands();
	while (1)
	{
		g_.pid_ch = 1;
		ft_read_line();
		add_history(g_.input);
		g_.i = 0;
		if (!ft_init())
		{
			free(g_.input);
			continue ;
		}
		check();
		g_.cmnd = -1;
	}
}
