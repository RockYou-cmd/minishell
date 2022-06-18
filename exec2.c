#include "minishell.h"

int print_exp()
{
	int i;

	i = 0;
	while(g.exp[i])
		printf("%s\n", g.exp[i++]);
	return 1;
}

void updt_export (char *str, int t)
{
	int i;
	int j;

	i = 0;
	j = 0;
	g.t = 0;
	if (is_iq(str, 0) != 9)
		g.exp[t] = ft_strdup(str);
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
		while(str[j])
			g.exp[t][i ++] = str[j ++];
		g.exp[t][i + 1] = 0;
	}
}

void set_export(char *str)
{
	int i;

	i = 0;
	while(g.exp[i])
		i ++;
	g.exp[i] = ft_strdup(str);
	printf("%s\n", g.exp[i]);
}

int var_check(char *var)
{
	int i;
	char *tmp;

	i = 0;
	while(var[i] != '=')
		i ++;
	tmp = malloc(i * sizeof(char));
	i = 0;
	while(var[i] != '=' && var[i] != '+')
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
	return 0;
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
		if (!var_check(str[i ++]))
			j++;
	}
	g.exp = ft_realloc(g.exp, j);
	i = 0;
	while (str[i])
	{
		if ((j = var_check(str[i])))
			updt_export (str[i++], j);
		else
			set_export(str[i++]);
	}
	return 0;
}

void ft_unset()
{

}
