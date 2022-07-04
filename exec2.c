/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:42:36 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **str, int i, int j)
{
	if (!str[0] || (str[0][0] == '-' && str[0][1] == '-' && str[0][2] == '\0'))
		return (print_exp());
	while (str[i])
		if (var_check(str[i ++], 0) == -1)
			j++;
	i = 0;
	while (g_.env[i])
		i ++;
	g_.env = ft_realloc(g_.env, j);
	i = 0;
	while (str[i])
	{
		if (!exp_sign(str[i]))
		{
			printf("minishell: export: not valid identifier\n");
			i ++;
			continue ;
		}
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
	ft_free(g_.env);
	if (!g_.pip)
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
	if (!g_.env)
		return (1);
	while (g_.env[i])
	{
		if (ft_strchr(g_.env[i], '='))
			printf("%s\n", g_.env[i]);
		i++;
	}
	return (0);
}

int	ft_unset(char	**str, int i, int j)
{
	if (str[0])
	{
		if (str[0][0] == '-' && ((str[0][1] != '\0' && str[0][1] != '-')
			|| (str[0][1] == '-' && str[0][2] != '\0')))
		{
			printf("minishell: unset: %s: invalid option\n", str[0]);
			return (1);
		}
	}
	if (!str)
		return (0);
	while (str[i])
	{
		if (!unset_pars(str[i]))
		{
			printf("minishell: unset: %s: not valid identifier\n", str[i ++]);
			continue ;
		}
		j = var_check(str[i ++], 0);
		if (j != -1)
			rm_var(j);
	}
	return (0);
}
