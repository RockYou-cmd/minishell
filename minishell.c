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

t_data g;

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

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;

	g.env = env;
	g.cmnd = -1;
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