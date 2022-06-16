#include "minishell.h"

int spce_ned(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' ' && str[i + 1] != str[i])
			len++;
		if ((str[i] == '>' || str[i] == '<') && str[i - 1] != ' ' && str[i - 1] != str[i])
			len ++;
		i ++;
	}
	return len;
}

char *add_spaces(char *str)
{
	int i;
	int t;
	char *ret;
	int d;
	int s;

	i = 0;
	t = 0;
	d = 0;
	s = 0;
	ret = malloc((spce_ned(str) + ft_strlen(str) + 1) * sizeof(char));
	while (str[i])
	{
		ooc(str[i], &s, &d);
		if ((str[i] == '>' || str[i] == '<') && str[i - 1] != ' ' && str[i - 1] != str[i] && d == 0 && s == 0)
			ret[t ++] = ' ';
		ret[t ++] = str[i];
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' ' && str[i + 1] != str[i] && d == 0 && s == 0)
			ret[t ++] = ' ';
		i ++;
	}
	ret[t] = 0;
	return ret;
}

int red_check(char *str)
{
	int i;
	char **ptp;

	i = 0;
	g.t = 0;
	g.i = 0;
	ptp = ft_split(add_spaces(str) , ' ');
	while (ptp[i])
	{
		if ((ft_strchr(ptp[i], '>') || ft_strchr(ptp[i], '<')) && (!(ft_strchr(ptp[i], '\'')) && !(ft_strchr(ptp[i], '\"'))))
		{
			if ((ft_strcmp(ptp[i], "<<") || ft_strcmp(ptp[i], ">>") || ft_strcmp(ptp[i], "<") || ft_strcmp(ptp[i], ">") ) && g.t == 0)
			{
				g.i = 1;
				g.t = 1;	
			}
			else
				return -1;
		}
		else
			g.t = 0;
		i ++;
	}
	ft_free(ptp);
	if (g.t == 1)
		return -1;
	return g.i;
}

int    cmd_len(char **str)
{
    int i;
    int l;

    i = 0;
    l = 0;

	while(str[i])
	{
		if ((ft_strcmp(str[i], "<<") || ft_strcmp(str[i], ">>") || ft_strcmp(str[i], "<") || ft_strcmp(str[i], ">") ))
			i ++;
		else
			l ++;
		i ++;
	}  	
    return (l);
}

void red_send(char *str)
{
	int i;
	int t;

	i = 0;
	t = 0;
	char **red;
	char **cmd;
	red = ft_split(add_spaces(str), ' ');
	cmd = malloc((cmd_len(red) + 1) * sizeof(char *));
	while(red[i])
	{
		if (ft_strcmp(red[i], "<<") || ft_strcmp(red[i], ">>") || ft_strcmp(red[i], "<") || ft_strcmp(red[i], ">"))
			find_red(red, i++);
		else
			cmd[t ++] = red[i];
		i ++;
	}
	// exec(cmd);
	// dup2(g.i_stdin , 0);
	// close(g.fd_stdin);
}