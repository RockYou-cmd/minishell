#include "minishell.h"

int print_exp()
{
	int i;

	i = 0;
	while(g.env[i])
		printf("%s\n", g.env[i++]);
	return 1;
}

void updt_export (char *str, int t)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (is_iq(str, 0) != 9 && g.i == 2)
	{
		free(g.env[t]);
		g.env[t] = ft_strdup(str);
	}
	else if (g.i != 2)
		return ;
	else
	{
		while(g.env[t][i])
			i ++;
		while(str[j++] != '=');
		g.env[t] = ft_rrealloc(g.env[t], ft_strlen(str + j));
		if (!ft_strchr(g.env[t], '='))
			g.env[t][i ++] = '=';
		while(str[j])
			g.env[t][i ++] = str[j ++];
		g.env[t][i + 1] = 0;
	}
}

void set_export(char *str)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	g.i = 0;
	g.t = 0;
	while(g.env[i])
		i ++;
	tmp = ft_split(str, '=');
	if (ft_strchr(tmp[0], '+'))
	{
		g.env[i] = malloc((ft_strlen(str) + 1) * sizeof(char));
		while(str[j])
		{
			if (str[j] == '+' && g.i != 1)
			{
				g.i = 1;
				j ++;
			}
			g.env[i][g.t ++] = str[j ++];
		}
		g.env[i][g.t] = 0;
	}
	else
		g.env[i] = ft_strdup(str);
	g.env[i + 1] = 0;
	ft_free(tmp);
}


int var_check(char *var)
{
	int i;
	char *tmp;
	char **s_env;

	i = 0;
	while(var[i] != '=' && var[i] != 0)
		i ++;
	tmp = malloc((i + 1) * sizeof(char));
	i = 0;
	while(var[i] != '=' && var[i] != '+' && var[i] != 0)
	{
		tmp[i] = var[i];
		i ++;
	}
	tmp[i] = 0;
	i = 0;
	while(g.env[i])
	{
		s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(s_env[0], tmp))
		{
			ft_free(s_env);
			free(tmp);
			return --i;
		}
		ft_free(s_env);
	}
	free(tmp);
	return -1;
}

int ft_export(char **str)
{
	int i;
	int j;
	int p;

	j = 0;
	i = 0;
	if (!(*str))
		return (print_exp());
	if (!(p = exp_sign(str)))
	{
		printf("not valid identifier\n");
		return 0;
	}
	while (str[i])
	{
		if (var_check(str[i ++]) == -1)
			j++;
	}
	i = 0;
	while(g.env[i])
		i ++;
	g.env = ft_realloc(g.env, j);
	i = 0;
	while (str[i])
	{
		if ((j = var_check(str[i])) != -1)
			updt_export (str[i++], j);
		else
			set_export(str[i++]);
	}
	return 0;
}
