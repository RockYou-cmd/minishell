#include "minishell.h"

char *v_env(char *str)
{
	int i;
	char *value;
	char *tmp;

	i = 0;
	g.t = 0;
	value = NULL;
	tmp = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i ++] != '$' && str[i + 1] != '\0');
	if (str[i - 1] != '$')
		return NULL;
	while(str[i] != 0 && str[i] != '$' && str[i] != '\"' && str[i] != ' ' && str[i] != '\'')
		tmp[g.t ++] = str[i++];
	i = 0;
	while(g.env[i])
	{
		g.s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(g.s_env[0], tmp))
			value = g.s_env[1];
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

void fill_env_exp(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i ++;
	g.exp = malloc((i + 1) * sizeof(char *));
	g.env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while(env[i])
	{
		g.exp[i] = env[i];
		g.env[i] = env[i];
		i ++;		
	}
	g.exp[i] = 0;
	g.env[i] = 0;
}

void ft_init()
{
	g.fd_stdin = 0;
	g.fd_stdout = 1;
	g.i = 0;
	g.cmd = malloc(sizeof(t_cmd));
	if (ft_strchr(g.input, '|') )
	{
		g.cmd->s_cmd = ft_split(g.input, '|');
		g.pip = 1;
	}
}