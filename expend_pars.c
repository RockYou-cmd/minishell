/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:42:31 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nrml_var(char *str, int j)
{
	if (!ft_isalpha(str[j]) && str[j++] != '_')
		return (0);
	while (str[j])
	{
		if (!ft_isalpha(str[j]) && !ft_isdigit(str[j]) && str[j] != '_')
			return (0);
		j ++;
	}
	return (1);
}

int	is_iq(char *str, int j)
{
	int	plus;

	plus = 1;
	g_.i = 0;
	if (ft_isalpha(str[j]) == 0 && str[j] != '_')
		return (0);
	j ++;
	while (str[j] != '=' && str[j] != 0)
	{
		if (!ft_isalpha(str[j]) && !ft_isdigit(str[j])
			&& str[j] != '_' && str[j] != '+')
			return (0);
		if (str[j] == '+' && str[j + 1] != '=')
			return (0);
		else if (str[j] == '+' && str[j + 1] == '=')
			plus = 9;
		j ++;
	}
	if (str[j] == '=')
		g_.i = 2;
	return (plus);
}

int	exp_sign(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strchr(str, '='))
	{
		if (!is_iq(str, 0))
			return (0);
	}
	else
	{
		if (!nrml_var(str, 0))
			return (0);
	}
	return (1);
}

void	rm_var(int j)
{
	int	i;

	if (!ft_strncmp(g_.env[j], "_=", 2))
		return ;
	i = j + 1;
	free(g_.env[j]);
	while (g_.env[i])
		g_.env[j++] = g_.env[i++];
	g_.env[j] = 0;
}

int	unset_pars(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i ++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i ++;
	}
	return (1);
}
