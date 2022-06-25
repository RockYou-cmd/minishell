#include "minishell.h"

int print_exp()
{
	int i;

	i = 0;
	while(g.exp[i])
		printf("%s\n", g.exp[i++]);
	printf("%d\n", i);
	return 1;
}

void updt_export (char *str, int t)
{
	int i;
	int j;

	i = 0;
	j = 0;
	g.t = 0;
	if (is_iq(str, 0) != 9 && g.i == 2)
		g.exp[t] = ft_strdup(str);
	else if (g.i != 2)
		return ;
	else
	{
		while(g.exp[t][i])
			i ++;
		while(str[j])
			j ++;
		while(str[--j] != '=')
			g.t ++;
		j++;
		g.exp[t] = ft_rrealloc(g.exp[t], g.t);
		if (!ft_strchr(g.exp[t], '='))
			g.exp[t][i ++] = '=';
		while(str[j])
			g.exp[t][i ++] = str[j ++];
		g.exp[t][i + 1] = 0;
	}
}

void set_export(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	g.i = 0;
	g.t = 0;
	while(g.exp[i])
		i ++;
	if (ft_strchr(*ft_split(str, '='), '+'))
	{
		g.exp[i] = malloc(ft_strlen(str) * sizeof(char));
		while(str[j])
		{
			if (str[j] == '+' && g.i != 1)
			{
				g.i = 1;
				j ++;
			}
			g.exp[i][g.t ++] = str[j ++];
		}
		g.exp[i][g.t] = 0;
	}
	else
		g.exp[i] = ft_strdup(str);
	g.exp[i + 1] = 0;
}

int var_check(char *var)
{
	int i;
	char *tmp;

	i = 0;
	while(var[i] != '=' && var[i] != 0)
		i ++;
	tmp = malloc(i * sizeof(char));
	i = 0;
	while(var[i] != '=' && var[i] != '+' && var[i] != 0)
	{
		tmp[i] = var[i];
		i ++;
	}
	tmp[i] = 0;
	i = 0;
	while(g.exp[i])
	{
		g.s_env = ft_split(g.exp[i++], '=');
		if (ft_strcmp(g.s_env[0], tmp))
			return --i;
		ft_free(g.s_env);
	}
	return -1;
}

int ft_export(char **str)
{
	int i;
	int j;
	int p;

	j = 0;
	i = 0;
	if (!str)
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
	while(g.exp[i])
		i ++;
	g.exp = ft_realloc(g.exp, j);
	i = 0;
	while (str[i])
	{
		if ((j = var_check(str[i])) != -1)
			updt_export (str[i++], j);
		else
			set_export(str[i++]);
	}
	exp_to_env();
	return 0;
}
