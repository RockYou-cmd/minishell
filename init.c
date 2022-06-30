#include "minishell.h"

char *v_env(char *str)
{
	int i;
	char *value;
	char *tmp;
	char **s_env;

	i = 0;
	g.t = 0;
	value = NULL;
	tmp = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i ++] != '$' && str[i ++] != '\0');
	if (str[i - 1] != '$')
	{
		free(tmp);
		return NULL;
	}
	if (!ft_isdigit(str[i]) && str[i] != '?')
	{
		while(str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
			tmp[g.t ++] = str[i++];
	}
	else
			tmp[g.t ++] = str[i++];
	i = 0;
	while(g.env[i])
	{
		s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(s_env[0], tmp))
			value = ft_strdup(s_env[1]);
		else if (ft_strcmp("?", tmp))
			value = ft_itoa(g.state);
		ft_free(s_env);
	}
	free(tmp);
	return value;
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

int pipe_check()
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(g.input[i])
	{
		if (g.input[i] != '|' && g.input[i] != ' ')
			j = 0;
		if (g.input[i] == '|' && j == 0)
			j = 1;
		else if (g.input[i] == '|' && j == 1 && g.input[i - 1] != '|')
			return 0;
		else if (g.input[i] == '|' && j == 1 && g.input[i - 1] == '|' && g.input[i - 2] == '|')
			return 0;
		i++;
	}
	if (!g.input[i] && j == 1)
		return 0;
	return 1;
}

int ft_init()
{
	g.fd_stdin = 0;
	g.fd_stdout = 1;
	g.i = 0;
	g.s_cmd = ft_split(g.input, '|');
	if (!g.s_cmd )
	{
		free(g.input);
		return 0;
	}
	if (ft_strchr(g.input, '|'))
	{
		if (!pipe_check())
		{
			free(g.input);
			ft_free(g.s_cmd);
			printf("minishell: syntax error: unexpected '|'\n");
			g.state = 258;
			return 0;
		}
		g.pip = 1;
	}
	if (!g.s_cmd[0])
	{
		free(g.input);
		ft_free(g.s_cmd);
		return 0;
	}
	return 1;
}