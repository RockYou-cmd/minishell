#include "minishell.h"

void	ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char **ft_realloc(char **str, int t)
{
	int i;
	char **ret;

	i = 0;
	while(str[i])
		i ++;
	ret = ft_calloc((i + t + 1) , sizeof(char *));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i ++;
	}
	ret[i] = 0;
	ft_free(str);
	return ret;
}

char *ft_rrealloc(char *str, int t)
{
	int i;
	char *ret;

	i = 0;
	while(str[i])
		i ++;
	ret = ft_calloc((i + t + 1) , sizeof(char *));
	t += i;
	i = 0;
	while (i < t)
	{
		ret[i] = str[i];
		i ++;
	}
	ret[i] = 0;
	free(str);
	return ret;
}
