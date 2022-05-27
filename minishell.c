/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:06:09 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/05/27 14:15:04 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int signm)
{
	if (signm == SIGINT)
	{
		write(1,"\n",1);
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
	else if (signm == SIGQUIT )
	{
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}	
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;

	g.env = env;
	g.cmnd = -1;
	g.i_stdin = dup(0);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	get_path();
	comands();
	while(1)
	{
		g.input = readline("minishell=>");
		if(!g.input)
		{
			write(1, up("1")right("12")"exit\n",15);
			exit(1);
		}
		add_history(g.input);
		ft_init();
		// printf("VALUE : %s\n", v_env(g.input));
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