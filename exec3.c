#include "minishell.h"

int var2_check(char *var)
{
	int i;
	char *tmp;
    char **s_env;

	i = 0;
	while(var[i] != '=' && var[i] != 0)
		i ++;
	tmp = malloc((1 + i) * sizeof(char));
	i = 0;
	while(var[i] != '=' && var[i] != 0)
	{
		tmp[i] = var[i];
		i ++;
	}
	tmp[i] = 0;
	i = 0;
	while(g.env[i])
	{
		s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(s_env[0], tmp))
        {
            free(tmp);
            ft_free(s_env);
			return (--i);
        }
		ft_free(s_env);
	}
    free(tmp);
	return (-1);
}

// void exp_to_env()
// {
//     int i;

//     i = 0;
//     while(g.exp[i])
//         i ++;
//     g.env = ft_calloc(i + 1, sizeof(char *));
//     i = 0;
//     while(g.exp[i])
//     {
//         g.env[i] = ft_strdup(g.exp[i]);
//         i ++;
//     }
//     g.env[i] = 0;
// }

void rm_var(int j)
{
    int i;

    i = j + 1;
    free(g.env[j]);
    while(g.env[i])
        g.env[j++] = g.env[i++];
    g.env[j] = 0;
}

void ft_unset(char **str)
{

    int i;
    int j;

    i = 0;
    j = 0;
    if (!str)
        return ;
    while (str[i])
    {
        if ((j = var2_check(str[i ++])) != -1)
            rm_var(j);
    }

}