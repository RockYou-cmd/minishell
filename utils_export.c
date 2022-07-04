/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:43:20 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_tab(int i, int n, int j)
{
	char	*tmp;
	char	**export;

	while (g_.env[i])
		i++;
	export = ft_calloc(i + 1, sizeof(char *));
	while (g_.env[++n])
		export[n] = ft_strdup(g_.env[n]);
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
	char	**export;

	g_.i = 0;
	export = sort_tab(0, -1, 0);
	while (export[g_.i])
	{
		if (export[g_.i][0] == '_' && export[g_.i][1] == '=')
		{
			g_.i ++;
			continue ;
		}
		g_.t = 0;
		printf("declare -x ");
		while (export[g_.i][g_.t] && export[g_.i][g_.t] != '=' )
			printf("%c", export[g_.i][g_.t++]);
		if (export[g_.i][g_.t] == '=' )
			printf("%c", export[g_.i][g_.t++]);
		if (export[g_.i][g_.t])
			printf("\"%s\"", &export[g_.i][g_.t]);
		printf("\n");
		g_.i++;
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
	if (is_iq(str, 0) != 9 && g_.i == 2 && (str[0] != '_' && str[1] != '='))
	{
		free(g_.env[t]);
		g_.env[t] = ft_strdup(str);
	}
	else if (g_.i != 2 || (str[0] == '_' && str[1] == '='))
		return ;
	else
	{
		while (g_.env[t][i])
			i ++;
		while (str[j++] != '=')
			;
		g_.env[t] = ft_rrealloc(g_.env[t], ft_strlen(str + j));
		if (!ft_strchr(g_.env[t], '='))
			g_.env[t][i ++] = '=';
		while (str[j])
			g_.env[t][i ++] = str[j ++];
		g_.env[t][i + 1] = 0;
	}
}

void	set_export(char	*str, int i, int j)
{
	char	**tmp;

	g_.i = 0;
	g_.t = 0;
	while (g_.env[i])
		i ++;
	tmp = ft_split(str, '=');
	if (ft_strchr(tmp[0], '+'))
	{
		g_.env[i] = malloc((ft_strlen(str) + 1) * sizeof(char));
		while (str[j])
		{
			if (str[j] == '+' && g_.i != 1)
			{
				g_.i = 1;
				j ++;
			}
			g_.env[i][g_.t ++] = str[j ++];
		}
		g_.env[i][g_.t] = 0;
	}
	else
		g_.env[i] = ft_strdup(str);
	g_.env[i + 1] = 0;
	ft_free(tmp);
}

int	var_check(char *var, int i)
{
	char	*tmp;
	char	**s_env;

	g_.i = 0;
	while (var[i] != '=' && var[i] != 0)
		i ++;
	tmp = malloc((i + 1) * sizeof(char));
	i = 0;
	while (var[i] != '=' && var[i] != '+' && var[i] != 0)
		tmp[i++] = var[g_.i++];
	tmp[i] = 0;
	i = 0;
	while (g_.env[i])
	{
		s_env = ft_split(g_.env[i++], '=');
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
