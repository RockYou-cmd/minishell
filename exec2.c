#include "minishell.h"

void ft_env()
{
    int i = 0;
    
    while (g.env[i])
    {
        printf("%s\n",g.env[i]);
        i++;
    }
}

void ft_exit()
{
	
}