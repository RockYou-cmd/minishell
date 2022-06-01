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

int calc()
{
	char *tmp;
	char *tmp2;
	int i;
	int t;

	i = 0;
	t = 0;
	while(g.input[i] != 0)
	{
		if (g.input[i] == '$')
		{
			tmp = *(ft_split(g.input + i, ' '));
			if (!(tmp2 = v_env(tmp)))
				t += 0;
			else
				t += strlen(tmp2);		
		}
		i ++;
	}
	return t;
}

int dolar(char *str, int s)
{
	int t;
	int i;
	int p;
	char *tmp;
	char *tmp2;

	t = 0;
	i = 0;
	p = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != 0 && str[i + 1] != '\"' && (str[i + 2] != ' '  || str[i + 2] != '\0'))
		{
			tmp = *(ft_split(str + i, ' '));
			if ((tmp2 = v_env(tmp)))
			{
				while(tmp2[p] != '\0')
					g.clr_cmd[s ++] = tmp2[p ++];
			}
			i += g.t + 1;
			p = 0;
		}
		else
			g.clr_cmd[s ++] = str[i ++];
	}
	return s;
}

int dolar2(char *str, int s)
{
	int t;
	int i;
	int p;
	char *tmp;
	char *tmp2;

	t = 0;
	i = 0;
	p = 0;
	while (str[g.i] != '\"' && str[g.i] != '\'' && str[g.i] != '\0')
	{
		if (str[g.i] == '$' && str[g.i + 1] != ' ' && str[g.i + 1] != 0 && str[g.i + 1] != '\"' && (str[g.i + 2] != ' '  || str[g.i + 2] != '\0'))
		{
			tmp = *(ft_split(str + g.i, ' '));
			if ((tmp2 = v_env(tmp)))
			{
				while(tmp2[p] != '\0')
					g.clr_cmd[s ++] = tmp2[p ++];
			}
			g.i += g.t + 1;
			p = 0;
		}
		else if (str[g.i]  == ' ')
		{
			g.clr_cmd[s ++] = '*';
			g.i ++;
		}
		else
			g.clr_cmd[s ++] = str[g.i ++];
	}
	g.i --;
	return s;
}

int squotes(int s, char *str)
{
	int t;
	int i;

	t = 0;
	i = 0;
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
	if (str[g.i] == '\"')
	{
		s = dolar(str + t , s);
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

	s = 0;
	printf("calc : %lu\n", (calc() + ft_strlen(str)));
	g.clr_cmd = ft_calloc(ft_strlen(str) + calc(), sizeof(char));
	printf("cmd : %s\n", str);
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
		else if (str[g.i] == ' ')
			g.clr_cmd[s ++] = '*';
		else
			s = dolar2(str, s);
		g.i ++;
	}
	g.clr_cmd[s] = 0;
	g.i = 0;
	return g.clr_cmd;
}

int heredoc_check(char *str)
{
	int i;
	int d;
	int s;

	i = 0;
	d = 0;
	s = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"')
		{
			if (d == 0)
				d = 1;
			else
				d = 0;
		}
		else if (str[i] == '\'')
		{
			if (s == 0)
				s = 1;
			else
				s = 0;
		}
		if (str[i] == '<' && str[i + 1] == '<' && d == 0 && s == 0)
			return 69;
		i ++;
	}
	return 0;

}

void check()
{
	int i;
	int t;
	int isnt;

	i = 0;
	t = 0;
	isnt = 0;
	
	// printf("check : %d\n", heredoc_check(g.input));
	if (g.pip == 1)
	{
		while(g.cmd->s_cmd[i + 1] != 0)
		{
			// if (heredoc_check(g.cmd->s_cmd[i]))
			// 	ft_heredoc();
			exec_v2(rm(g.cmd->s_cmd[i]));
			i ++;
		}
		exec(rm(g.cmd->s_cmd[i]));
		dup2(g.i_stdin, 0);
		dup2(g.i_stdout, 1);
		g.pip = 0;
	}
	else
		exec(rm(g.input));
	}