#include "minishell.h"

int	ft_export(char **str, int i, int j, int p)
{
	if (!(*str))
		return (print_exp());
	p = exp_sign(str);
	if (!p)
	{
		printf("not valid identifier\n");
		return (0);
	}
	while (str[i])
		if (var_check(str[i ++], 0) == -1)
			j++;
	i = 0;
	while (g.env[i])
		i ++;
	g.env = ft_realloc(g.env, j);
	i = 0;
	while (str[i])
	{
		j = var_check(str[i], 0);
		if (j != -1)
			updt_export (str[i++], j);
		else
			set_export(str[i++], 0, 0);
	}
	return (0);
}

void	ft_exit(void)
{
	/*free_all();*/
	printf("exit\n");
	exit(0);
}

int	ft_env(void)
{
	int	i;

	i = 0;
	if (!g.env)
		return (1);
	while (g.env[i])
	{
		if (ft_strchr(g.env[i], '='))
			printf("%s\n", g.env[i]);
		i++;
	}
	return (0);
}

void	rm_var(int j)
{
	int	i;

	i = j + 1;
	free(g.env[j]);
	while (g.env[i])
		g.env[j++] = g.env[i++];
	g.env[j] = 0;
}

void	ft_unset(char	**str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return ;
	while (str[i])
	{
		j = var_check(str[i ++], 0);
		if (j != -1)
			rm_var(j);
	}
}
