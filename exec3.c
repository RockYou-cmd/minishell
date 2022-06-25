#include "minishell.h"

int var2_check(char *var)
{
	int i;
	char *tmp;

	i = 0;
	while(var[i] != '=' && var[i] != 0)
		i ++;
	tmp = malloc((1 + i) * sizeof(char));
	i = 0;
	while(var[i] != '=' && var[i] != '+' && var[i] != 0)
	{
		tmp[i] = var[i];
		i ++;
	}
	tmp[i] = 0;
	i = 0;
	while(g.env[i])
	{
		g.s_env = ft_split(g.env[i++], '=');
		if (ft_strcmp(g.s_env[0], tmp))
			return --i;
		ft_free(g.s_env);
	}
	return -1;
}

void exp_to_env()
{
    int i;

    i = 0;
    while(g.exp[i])
        i ++;
    g.env = ft_calloc(i + 1, sizeof(char *));
    i = 0;
    while(g.exp[i])
    {
        g.env[i] = ft_strdup(g.exp[i]);
        i ++;
    }
    g.env[i] = 0;
}

void rm_var(int j)
{
    int i;
    int t;

    i = 0;
    t = 0;
    while(g.env[i])
    {
        if (j != i)
            g.exp[t ++] = g.env[i];
        i ++;
    }
    g.exp[t] = 0;
}

void ft_unset(char **str)
{   
    int i;
    int j;

    i = 0;
    j = 0;
    if (!str)
    {
        printf("not enough argumens!\n");
        return ;
    }    
    while (str[i])
	{
		if (var2_check(str[i ++]) != -1)
			j++;
	}
    i = 0;
    while(g.exp[i])
        i ++;
    g.exp = ft_calloc(i - j + 1, sizeof(char *));
    i = 0;
    while(str[i])
    {
        if ((j = var2_check(str[i])) != -1)
            rm_var(j);
        exp_to_env();
        i ++;
    }
}

