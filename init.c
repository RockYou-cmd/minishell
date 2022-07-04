/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:42:39 by ael-korc          #+#    #+#             */
/*   Updated: 2022/07/04 21:26:35 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *tmp)
{
	char	**s_env;
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (g_.env[i])
	{
		s_env = ft_split(g_.env[i++], '=');
		if (ft_strcmp(s_env[0], tmp))
			value = ft_strdup(s_env[1]);
		else if (ft_strcmp("?", tmp))
			value = ft_itoa(g_.state);
	}
	return (value);
}

char	*v_env(char *str)
{
	int		i;
	char	*value;
	char	*tmp;

	i = 0;
	g_.t = 0;
	value = NULL;
	tmp = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i] != '$' && str[i] != '\0')
		i ++;
	if (str[i++] != '$')
	{
		free(tmp);
		return (0);
	}
	if (!ft_isdigit(str[i]) && str[i] != '?')
		while (str[i] && (ft_isalpha(str[i])
				|| ft_isdigit(str[i]) || str[i] == '_'))
			tmp[g_.t ++] = str[i++];
	else
		tmp[g_.t ++] = str[i++];
	i = 0;
	value = ft_getenv(tmp);
	free(tmp);
	return (value);
}

void	comands(void)
{
	g_.command[0] = "echo";
	g_.command[1] = "cd";
	g_.command[2] = "pwd";
	g_.command[3] = "export";
	g_.command[4] = "unset";
	g_.command[5] = "env";
	g_.command[6] = "exit";
	g_.command[7] = 0;
}

char	**esp_splt(char *str)
{
	char	**tmp;
	char	**ret;
	int		i;

	i = 0;
	tmp = ft_split(str, ' ');
	while (tmp[i++])
		;
	ret = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp[i])
	{
		ret[i] = rm(tmp[i]);
		i ++;
	}
	ret[i] = 0;
	ft_free(tmp);
	return (ret);
}

int	ft_init(void)
{
	g_.s_cmd = ft_split(g_.input, '|');
	if (!g_.s_cmd)
	{
		g_.state = 1;
		return (0);
	}
	if (ft_strchr(g_.input, '|'))
	{
		if (!pipe_check(0, 1))
		{
			ft_free(g_.s_cmd);
			printf("minishell: syntax error: unexpected '|'\n");
			g_.state = 258;
			return (0);
		}
		g_.pip = 1;
	}
	if (!g_.s_cmd[0])
	{
		ft_free(g_.s_cmd);
		return (0);
	}
	return (1);
}
