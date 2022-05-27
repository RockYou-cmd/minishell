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

int dolar()
{
	char *ret;
	int p;
	int i;
	char *tmp;
	int t;

	p = 0;
	i = 0;
	t = 0;
	while(g.clr_cmd[i] != '$')
		i ++;
	if (g.clr_cmd[i] == '$')
	{
		ret = v_env(*(ft_split(g.clr_cmd + i, ' ')));
		tmp = ft_calloc(ft_strlen(ret) + ft_strlen(g.clr_cmd), sizeof(char));
		while(g.clr_cmd[p] != '$')
			tmp[t++] = g.clr_cmd[p];
	}
	return p;
}

int squotes(int s, char *str)
{
	int t;

	t = 0;
	t = ++g.i;
	while(str[g.i] != '\'' && str[g.i] != 0)
		g.i++;
	if (str[g.i] == '\'')
	{
		while(str[t] != '\'')
			g.clr_cmd[s++] = str[t++];
	}
	else
	{
		printf("quote ' error\n");
		return -1;
	}
	return s;
}

int dquotes (int s , char *str)
{
	int t;

	t = 0;
	t = ++g.i;
	while(str[g.i] != '\"' && str[g.i] != 0)
		g.i++;
	// printf("-%c-\n", g.input[g.i]);
	if (str[g.i] == '\"')
	{
		while(str[t] != '\"')
			g.clr_cmd[s++] = str[t++];
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
	g.i = 0;
	s = 0;
	g.clr_cmd = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[g.i] != 0)
	{
		if (str[g.i] == '\'')
		{
			if ((s = squotes(s, str)) == -1)
				return 0;
		}	
		else if (str[g.i] == '\"')
		{
			if ((s = dquotes(s, str)) == -1)
				return 0;
		}
		else if (str[g.i] == ' ' && (str[g.i + 1] == ' ' || str[g.i + 1] == '\0'));
		else
			g.clr_cmd[s++] = str[g.i];
		g.i ++;
	}
	g.i = 0;
	// dolar();
	return g.clr_cmd;
}

void check()
{
	int i;
	int t;
	int isnt;

	i = 0;
	t = 0;
	isnt = 0;
	// printf("cmd : %s\n", g.clr_cmd);
	if (g.pip == 1)
	{
		while(g.cmd->s_cmd[i + 1] != 0)
		{
			exec_v2(rm(g.cmd->s_cmd[i]));
			i ++;
		}
		printf("cmd : %s\n", g.cmd->s_cmd[i]);
		exec(rm(g.cmd->s_cmd[i]));
		dup2(g.i_stdin, 0);

		// printf("-%s-\n", rm(g.cmd->s_cmd[0]));
	}
	else
		exec(rm(g.input));
		// printf("%s\n", rm(g.input));
}