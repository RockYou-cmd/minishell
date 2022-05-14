#include "minishell.h"

void which_one(int i)
{
	if (g.cmnd == 0)
		ft_echo(i);
	if (g.cmnd == 1)
		ft_cd();
	if (g.cmnd == 2)
		ft_pwd();
	if (g.cmnd == 3)
		ft_export();
	if (g.cmnd == 4)
		ft_unset();
	if (g.cmnd == 5)
		ft_env();
	if (g.cmnd == 6)
		ft_exit();
	
}

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

void check()
{
	int i;
	int t;

	i = 0;
	t = 0;
	while(g.input[i] != ' ' && g.input[i] != '\0')
		i++;
	char command[i];
	i = 0;
	while (g.input[i] != ' ' && g.input[i] != '\0')
	{
		command[i] = g.input[i];
		i ++;
	}
	command[i] = 0;
	// printf("%d - %s\n", ft_strncmp(command, g.command[t], i), command);
	while(g.command[t] != 0)
	{
		if (ft_strncmp(command, g.command[t], i) == 0)
			g.cmnd = t;
		t ++;

	}
	// if (g.cmnd != -1)
	// 	printf("the  command is %s\n", g.command[g.cmnd]);
	// else
	// 	printf("%s : command not found\n", g.input);
	which_one(i);
	
}