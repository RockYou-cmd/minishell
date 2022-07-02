#include "minishell.h"

char	**sort_tab(int i, int n, int j)
{
	char	*tmp;
	char	**export;

	while (g.env[i])
		i++;
	export = ft_calloc(i + 1, sizeof(char *));
	while (g.env[++n])
		export[n] = ft_strdup(g.env[n]);
	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(export[i], export[j], ft_strlen(export[i])) > 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (export);
}

int	print_exp(void)
{
	int		i;
	int		j;
	char	**export;

	i = 0;
	export = sort_tab(0, -1, 0);
	while (export[i])
	{
		if (export[i][0] == '_' && export[i][1] == '=')
		{
			i ++;
			continue;
		}
		j = 0;
		printf("declare -x ");
		while (export[i][j] && export[i][j] != '=' )
			printf("%c", export[i][j++]);
		if (export[i][j] == '=' )
			printf("%c", export[i][j++]);
		if (export[i][j])
			printf("\"%s\"", &export[i][j]);
		printf("\n");
		i++;
	}
	ft_free(export);
	return (0);
}

void	updt_export(char *str, int t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (is_iq(str, 0) != 9 && g.i == 2 && (str[0] != '_' && str[1] != '='))
	{
		free(g.env[t]);
		g.env[t] = ft_strdup(str);
	}
	else if (g.i != 2 || (str[0] == '_' && str[1] == '='))
		return ;
	else
	{
		while (g.env[t][i])
			i ++;
		while (str[j++] != '=')
			;
		g.env[t] = ft_rrealloc(g.env[t], ft_strlen(str + j));
		if (!ft_strchr(g.env[t], '='))
			g.env[t][i ++] = '=';
		while (str[j])
			g.env[t][i ++] = str[j ++];
		g.env[t][i + 1] = 0;
	}
}

void	set_export(char	*str, int i, int j)
{
	char	**tmp;

	g.i = 0;
	g.t = 0;
	while (g.env[i])
		i ++;
	tmp = ft_split(str, '=');
	if (ft_strchr(tmp[0], '+'))
	{
		g.env[i] = malloc((ft_strlen(str) + 1) * sizeof(char));
		while (str[j])
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

int	var_check(char *var, int i)
{
	char	*tmp;
	char	**s_env;

	g.i = 0;
	while (var[i] != '=' && var[i] != 0)
		i ++;
	tmp = malloc((i + 1) * sizeof(char));
	i = 0;
	while (var[i] != '=' && var[i] != '+' && var[i] != 0)
		tmp[i++] = var[g.i++];
	tmp[i] = 0;
	i = 0;
	while (g.env[i])
	{
		s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(s_env[0], tmp))
		{
			ft_free(s_env);
			free(tmp);
			return (--i);
		}
		ft_free(s_env);
	}
	free(tmp);
	return (-1);
}