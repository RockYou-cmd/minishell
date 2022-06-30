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

void free_all()
{
	ft_free(g.path);
	ft_free(g.env);
}

void handler(int signm)
{
	if (signm == SIGINT && g.pid_ch == 1337)
	{
		write(1,"\n",1);
		rl_replace_line("",0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signm == SIGINT)
	{
		write(1,"\n",1);
		rl_replace_line("",0);
		rl_redisplay();
	}
	g.state = 1;
}

void	ft_read_line()
{
	g.input = readline("minishell-3.2$ ");
	if(!g.input)
	{
		write(1, "\033[1A\033[15Cexit\n",14);
		free_all();
		exit(1);
	}
}

void build_env(char **env)
{
	int i;
	int k;
	char *v;
	char *s;

	i = 0;
	while (env[i])
		i++;
	g.env = malloc((i+1) * sizeof(char *));
	i = -1;
	while(env[++i])
		g.env[i] = ft_strdup(env[i]);
	g.env[i] = 0;
	i = 0;
	while (g.env[i])
	{
		if (!strncmp(g.env[i],"SHLVL=" , 6))
		{
			v = ft_strchr(g.env[i],'=');
			++v;
			k = ft_atoi(v)+1;
			if(k < 0)
				k = 0;
			free(g.env[i]);
			s = ft_itoa(k);
			g.env[i] = ft_strjoin(ft_strdup("SHLVL="), s);
			free(s);
		}
		i++;
	}
	if (!env[0])
	{
		ft_free(g.env);
		g.env = NULL;
	}
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
	signal(SIGQUIT, SIG_IGN);
	get_path();
	comands();
	while(1)
	{
		g.pid_ch = 1337;
		ft_read_line();
		add_history(g.input);
		if(!ft_init())
			continue;
		check();
		g.cmnd = -1;
	}
	return (0);
}
