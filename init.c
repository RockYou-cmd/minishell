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
	while(str[i] != 0 && str[i] != '$' && str[i] != '\"' && str[i] != ' ' && str[i] != '\'')
		tmp[g.t ++] = str[i++];
	i = 0;
	while(g.env[i])
	{
		s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(s_env[0], tmp))
			value = ft_strdup(s_env[1]);
		ft_free(s_env);
	}
	free(tmp);
	return value;
}

void	comands(void)
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
	if (!g.s_cmd[0])
	{
		free(g.input);
		ft_free(g.s_cmd);
		return 0;
	}
	if (ft_strchr(g.input, '|'))
		g.pip = 1;
	return 1;
}