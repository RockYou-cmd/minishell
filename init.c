#include "minishell.h"

void comands()
{
	g.command[0] = "echo";
	g.command[1] = "cd";
	g.command[2] = "pwd";
	g.command[3] = "export";
	g.command[4] = "unset";
	g.command[5] = "env";
	g.command[6] = "exit";
	g.command[7] = 0;
}

void ft_init()
{
	g.cmd = malloc(sizeof(t_cmd));
	if (!ft_strchr(g.input, '|'))
	{
		g.cmd->s_cmd = ft_split(g.input, ' ');
		g.pip = 0;
	}
	else
	{
		g.cmd->s_cmd = ft_split(g.input, '|');
		g.pip = 1;
	}
}