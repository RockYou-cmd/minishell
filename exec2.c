#include "minishell.h"

int	ft_export(char **str, int i, int j)
{
	if (!str[0] || (str[0][0] == '-' && str[0][1] == '-' && str[0][2] == '\0'))
		return (print_exp());
	if (!exp_sign(str))
	{
		printf("minishell: export: not valid identifier\n");
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

void	ft_exit(char **str)
{
	int	i;

	i = -1;
	ft_free(g.env);
	printf("exit\n");
	if (!str[0])
		exit(1);
	if (str[1])
	{
		printf("minishell : exit: too many arguments\n");
		exit(1);
	}
	if (str[0][0] == '-' || str[0][0] == '+')
		i++;
	while (str[0][++i])
	{
		if (str[0][i] < '0' || str[0][i] > '9')
		{
			printf("minishell: exit: illegal number: %s\n", str[0]);
			exit(1);
		}
	}
	exit(ft_atoi(str[0]));
	exit(0);
}

int	ft_env(char **str)
{
	int	i;

	if (str[0])
	{
		printf("minishell: env: %s: No such file or directory\n", str[0]);
		return (1);
	}
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

	if (!ft_strncmp(g.env[j], "_=", 2))
		return ;
	i = j + 1;
	free(g.env[j]);
	while (g.env[i])
		g.env[j++] = g.env[i++];
	g.env[j] = 0;
}

int	ft_unset(char	**str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0])
	{
		if (str[0][0] == '-' && ((str[0][1] != '\0' && str[0][1] != '-')
			|| (str[0][1] == '-' && str[0][2] != '\0')))
		{
			printf("minishell: pwd: %s: invalid option\n", str[0]);
			return (1);
		}
	}
	if (!str)
		return (0);
	while (str[i])
	{
		j = var_check(str[i ++], 0);
		if (j != -1)
			rm_var(j);
	}
	return (0);
}
