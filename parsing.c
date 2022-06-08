#include "minishell.h"

void which_one(char **str)
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

int calc(char *str)
{
	char *tmp2;
	int i;
	int t;

	i = 0;
	t = 0;
	if (!(tmp2 = v_env(str)))
		t += 0;
	else
		t += ft_strlen(tmp2);		
	return t;
}

int dolar(char *str, int s)
{
	int t;
	int i;
	int p;
	char *tmp2;

	t = 0;
	i = 0;
	p = 0;
	while (str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != 0 && str[i + 1] != '\"' && (str[i + 2] != ' '  || str[i + 2] != '\0'))
		{
			if ((tmp2 = v_env(str + i)))
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
	int i;
	int p;
	char *tmp;
	char *tmp2;

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
		else if (str[g.i] == ' ' && str[g.i + 1] == ' ')
			g.i ++;
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
	g.clr_cmd = ft_calloc(ft_strlen(str) + calc(str), sizeof(char));
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
		else if (str[g.i] == ' ' && str[g.i + 1] == ' ');
		else
			s = dolar2(str, s);
		g.i ++;
	}
	g.clr_cmd[s] = 0;
	g.i = 0;
	return g.clr_cmd;
}

void ooc(char c, int *s, int *d)
{
	if (c == '\"')
	{
		if (*d == 0)
			*d = 1; 
		else
			*d = 0;
	}
	else if (c == '\'')
	{
		if (*s == 0)
			*s = 1;
		else
			*s = 0;
	}
}

int heredoc_check(char *str)
{
	int i;
	int d;
	int s;
	int al;
	int c;
	int j;

	i = 0;
	j = 0;
	d = 0;
	c = 0;
	s = 0;
	al = 0;
	while (str[i] != 0)
	{
		ooc(str[i], &s, &d);
		if (str[i] != '<' && str[i] != 0 && str[i] != ' ')
		{
			al = 0;
			c = 1;
		}
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<' && str[i - 1] != '<' && d == 0 && s == 0)
		{
			j = 1;
			i ++;
			if (c == 0 && al != 0)
				return -1;
			al = 69;
			c = 0;
		}	
		i ++;
	}
	if (al != 0)
		return -1;
	else
		return j;

}

char *heredoc_rm(char **str)
{
	int i;

	i = 0;
	while(str[i + 1] != 0)
	{
		str[0] = ft_strjoin(str[0], " ");
		str[0] = ft_strjoin(str[0], str[i + 1]);
		i ++;
	}
	return rm(str[0]);
}

char **esp_splt(char *str)
{
	char **tmp;
	char **ret;
	int i;

	i = 0;
	tmp = ft_split(str, ' ');
	i = 0;
	while(tmp[i++]);
	ret = malloc(i * sizeof(char *));
	i = 0;
	while(tmp[i])
	{
		ret[i] = rm(tmp[i]);
		i ++;
	}
	ret[i] = 0;
	ft_free(tmp);
	return (ret);
}

void check()
{
	int i;

	i = 0;
	if (g.pip == 1)
	{
		while(g.cmd->s_cmd[i + 1] != 0)
		{
			if (heredoc_check(g.cmd->s_cmd[i]))
				ft_heredoc(esp_splt(g.cmd->s_cmd[i]));
			else
				exec_v2(esp_splt(g.cmd->s_cmd[i]));
			i ++;
		}
		if (heredoc_check(g.cmd->s_cmd[i]))
				ft_heredoc(esp_splt(g.cmd->s_cmd[i]));
		else
			exec(esp_splt(g.cmd->s_cmd[i]));
		dup2(g.i_stdin, 0);
		dup2(g.i_stdout, 1);
		g.pip = 0;
	}
	else
	{
		if(heredoc_check(g.input) == -1)
			printf("parse error\n");
		else if (heredoc_check(g.input))
				ft_heredoc(esp_splt(g.input));
		else
			exec(esp_splt(g.input));
	}
}
