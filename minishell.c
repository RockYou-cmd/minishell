/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:06:09 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/05/11 20:25:42 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) av;
	(void) ac;
	(void) env;

	g.cmnd = -1;
	comands();
	while(1)
	{
		g.input = readline("type here > : ");
		if(!g.input)
		{
			printf("\n");
			continue;
		}
		add_history(g.input);
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