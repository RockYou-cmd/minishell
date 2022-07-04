/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:42:31 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/03 18:42:32 by ael-korc         ###   ########.fr       */
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
	g.i = 0;
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
		g.i = 2;
	return (plus);
}

int	exp_sign(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		if (ft_strchr(str[i], '='))
		{
			j = is_iq(str[i], j);
			if (!j)
				return (0);
		}
		else
		{
			j = nrml_var(str[i], j);
			if (!j)
				return (0);
		}
		i ++;
	}
	return (1);
}
