#include "minishell.h"

void which_one(char **str)
{
	g.state = 0;
	if (g.cmnd == 0)
		g.state = ft_echo(str);
	if (g.cmnd == 1)
		g.state = ft_cd(str);
	if (g.cmnd == 2)
		g.state = ft_pwd();
	if (g.cmnd == 3)
		g.state = ft_export(str);
	if (g.cmnd == 4)
		ft_unset(str);
	if (g.cmnd == 5)
		g.state = ft_env();
	if (g.cmnd == 6)
		ft_exit();
}

int calc(char *str)
{
	char *tmp2;
	int t;
	t = 0;
	if (!(tmp2 = v_env(str)))
		t += 0;
	else
		t += ft_strlen(tmp2);	
	free(tmp2);

	return t;
}

int dolar(char *str, int s)
{
	int i;
	int p;
	char *tmp2;

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
			free(tmp2);
		}
		else
			g.clr_cmd[s ++] = str[i ++];
	}
	return s;
}

int dolar2(char *str, int s)
{
	int p;
	char **tmp;
	char *tmp2;
	p = 0;
	while (str[g.i] != '\"' && str[g.i] != '\'' && str[g.i] != '\0')
	{
		if (str[g.i] == '$' && str[g.i + 1] != ' ' && str[g.i + 1] != 0 && str[g.i + 1] != '\"' && (str[g.i + 2] != ' '  || str[g.i + 2] != '\0'))
		{
			tmp = ft_split(str + g.i, ' ');
			if ((tmp2 = v_env(tmp[0])))
			{
				while(tmp2[p] != '\0')
					g.clr_cmd[s ++] = tmp2[p ++];
			}
			ft_free(tmp);
			free(tmp2);
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

	t = 0;
	t = ++g.i;
	while(str[g.i] != '\'' && str[g.i] != 0)
		g.i++;
	if (str[g.i] == '\'')
		while(str[t] != '\'')
			g.clr_cmd[s++] = str[t++];
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
		s = dolar(str + t , s);
	return s;
}

char *rm(char *str)
{
	int s;

	s = 0;
	g.i = 0;
	g.clr_cmd = ft_calloc(ft_strlen(str) + calc(str), sizeof(char));
	while (str[g.i] != 0)
	{
		if (str[g.i] == '\'')
			s = squotes(s, str);
		else if (str[g.i] == '\"')
			s = dquotes(s, str);
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
		if (*d == 0 && *s == 0)
			*d = 1; 
		else
			*d = 0;
	}
	else if (c == '\'' && *d == 0)
	{
		if (*s == 0)
			*s = 1;
		else
			*s = 0;
	}
}

// int err_check(char *str, int i, int d, int s)
// {
// 	i += 2;
// 	while(str[i] != 0)
// 	{
// 		if (str[i] == '<')
// 			return 44;
// 	}
// 	return i;
// }

int heredoc_check(char *str, int i)
{
	int d;
	int s;

	d = 0;
	g.i = 0;
	s = 0;
	g.t = 0;
	while (str[i] != 0)
	{
		ooc(str[i], &s, &d);
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<' && str[i - 1] != '<' && d == 0 && s == 0)
		{
			i ++;
			g.t = 1;
		}
		i ++;
		if (str[i] == '<')
			return -1;
	}
	return 1;
}

// int redirection_check(char *str)
// {
// 	if (heredoc_check(g.input, 0))
// 	{

// 	}
// }

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
	while(tmp[i++]);
	ret = malloc((i + 1 )* sizeof(char *));
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
	int r;

	i = 0;
	r = 0;
	// printf("%s\n", g.input);
	if (g.pip == 1)
	{
		while(g.s_cmd[i + 1] != 0)
		{
			r = red(g.s_cmd[i]);
			if (r == -1)
				return ;
			else if (r)
				red_send(g.s_cmd[i],1);
			else
				exec_v2(esp_splt(g.s_cmd[i]));
			i ++;
		}
		r = red(g.s_cmd[i]);
		if (r == -1)
			return ;
		else if (r)
			red_send(g.s_cmd[i],0);
		else
			exec(esp_splt(g.s_cmd[i]));		
		dup2(g.i_stdin, 0);
		dup2(g.i_stdout, 1);
		g.pip = 0;
	}
	else
	{
		r = red(g.input);
		if (r == -1)
			return ;
		else if (r)
			red_send(g.input,0);
		else
			exec(esp_splt(g.input));
	}
	free(g.input);
	ft_free(g.s_cmd);
}
