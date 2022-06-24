/* ************************************************************************** */
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
}

void	ft_read_line()
{
	g.input = readline("type here > : ");
	if(!g.input)
	{
		write(1, "\033[1A\033[14Cexit\n",14);
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
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;

	build_env(env);
	g.cmnd = -1;
	g.state = 0;
	g.i_stdin = dup(0);
	g.i_stdout = dup(1);
	fill_export();
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
	get_path();
	comands();
	while(1)
	{
		g.pid_ch = 1337;
		ft_read_line();
		add_history(g.input);
		ft_init();
		check();
		g.cmnd = -1;
	}
	return (0);
}
// func get env while prompt 
/*
unset remove var
env lisrt var
export > with arg >> add variable | no arg env  declare -x var = val
cd >> old pwd  pwd

*/

//chdir = cd
// getcwd = pwd