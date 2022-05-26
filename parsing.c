#include "minishell.h"

void which_one(char *str)
{
	if (g.cmnd == 0)
		ft_echo(str);
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

int dolar(char *str, int s, int t)
{
	char *ret;
	int p;

	p = 0;		
	if((ret = v_env(*(ft_split(&str[g.i], ' ')))))
	{
		printf("ret : %s\n", ret);
		while(ret[p] != 0 || ret[p] != '"')
			g.clr_cmd[s++] = ret[p++];
		while(str[t] != ' ' && str[t] != '\0' && str[t] != '"')
			t++;
	}
	return t;
}

int squotes(int s)
{
	int t;

	t = 0;
	t = ++g.i;
	while(g.input[g.i] != '\'' && g.input[g.i] != 0)
		g.i++;
	if (g.input[g.i] == '\'')
	{
		while(g.input[t] != '\'')
		{
			// if (g.input[t] == '$')
			// 	t = dolar(&g.input[t], s, t);
			// else
				g.clr_cmd[s++] = g.input[t++];
		}
	}
	else
	{
		printf("quote ' error\n");
		return -1;
	}
	return s;
}

int dquotes (int s)
{
	int t;

	t = 0;
	t = ++g.i;
	while(g.input[g.i] != '\"' && g.input[g.i] != 0)
		g.i++;
	// printf("-%c-\n", g.input[g.i]);
	if (g.input[g.i] == '\"')
	{
		while(g.input[t] != '\"')
			g.clr_cmd[s++] = g.input[t++];
	}
	else
	{
		printf("quote \" error\n");
		return -1;
	}
	return s;
}

char *rm(char *str)
{
	int s;
	// int p;

	g.i = 0;
	s = 0;
	g.clr_cmd = ft_calloc(100, sizeof(char));
	while (str[g.i] != 0)
	{
		if (str[g.i] == '\'')
		{
			if ((s = squotes(s)) == -1)
				return 0;
		}	
		else if (str[g.i] == '\"')
		{
			if ((s = dquotes(s)) == -1)
				return 0;
		}
		else if (str[g.i] == ' ' && (str[g.i + 1] == ' ' || str[g.i + 1] == '\0'));
		else
			g.clr_cmd[s++] = g.input[g.i];
		g.i ++;
	}

	return (g.clr_cmd);
}

void check()
{
	int i;
	int t;
	int isnt;

	i = 0;
	t = 0;
	isnt = 0;

	if (g.pip == 1)
	{
		while(g.cmd->s_cmd[i + 1] != 0)
		{
			// printf("cmd : %s\n", g.cmd->s_cmd[i]);
			exec_v2(g.cmd->s_cmd[i]);
			i ++;
		}
		exec(g.cmd->s_cmd[i]);
		dup2(g.i_stdin, 0);

		// printf("-%s-\n", rm(g.cmd->s_cmd[0]));
	}
	else
		exec(rm(g.input));
		// printf("%s\n", rm(g.input));
}