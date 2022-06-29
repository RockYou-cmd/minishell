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
	char *tmp;

	i = 0;
	g.t = 0;
	g.i = 0;
	tmp = add_spaces(str);
	ptp = ft_split(tmp , ' ');
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
	free(tmp);
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

void red_send(char *str, int pip)
{
	char **red;
	char **cmd;
	char *tmp;
	int i;
	int t;
	int output;

	i = 0;
	t = 0;
	output = 1;
	tmp = add_spaces(str);
	red = ft_split(tmp, ' ');
	free(tmp);
	cmd = malloc((cmd_len(red) + 1) * sizeof(char *));
	while(red[i])
	{
		if (ft_strcmp(red[i], "<<") || ft_strcmp(red[i], ">>") || ft_strcmp(red[i], "<") || ft_strcmp(red[i], ">"))
			find_red(red, i++,&output);
		else
			cmd[t ++] = ft_strdup(red[i]);
		i++;
	}
	cmd[t] = 0;
	if(g.fd_stdin != -1 && g.fd_stdout != -1)
	{
		dup2(g.fd_stdin , 0);
		dup2(g.fd_stdout , 1);
		if (pip && output)
			exec_v2(cmd);
		else
		{
			exec(cmd);
			if (!output && pip)
			{
				pipe(g.pipefd);
				dup2(g.pipefd[0],0);
				close(g.pipefd[1]);
				close(g.pipefd[0]);
			}
			else
				dup2(g.i_stdin, 0);
			dup2(g.i_stdout, 1);
		}
	}
	else
	{
		dup2(g.i_stdin, 0);
		dup2(g.i_stdout, 1);
		close(g.fd_stdin);
		printf("Error: no file descriptor : %s\n", g.file);
		ft_free(cmd);
		free(g.file);
	}
	ft_free(red);
	// printf("cmd : ****************%s\n", cmd[0]);
}