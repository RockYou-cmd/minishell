#include "minishell.h"

char *v_env(char *str)
{
	int i;
	char *value;

	i = 0;
	while(g.env[i])
	{
		g.s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(g.s_env[0], str + 1) == 0)
			value = g.s_env[1];
	}
	return value;
}

void comands()
{
	g.command[0] = "echo";
	g.command[1] = "cd";
	g.command[2] = "pwd";
	g.command[3] = "export";
	g.command[4] = "unset";
	g.command[5] = "ent";
	g.command[6] = "exit";
	g.command[7] = 0;
}

void ft_init()
{
	g.i = 0;
	g.cmd = malloc(sizeof(t_cmd));
	if (ft_strchr(g.input, '|'))
	{
		g.cmd->s_cmd = ft_split(g.input, '|');
		g.pip = 1;
	}
}