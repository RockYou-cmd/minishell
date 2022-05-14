#include "minishell.h"

int ft_echo(int i)
{
	int t;

	t = 0;
	// checker(i);
	while(g.input[i] == ' ')
		i++;
	while(g.input[i] != 0)
	{
		if (g.input[i] == '\'' || g.input[i] == '\"')
		{
			t = i;
			if (g.input[i] == '\'')
			{
				i ++;
				while(g.input[i] != '\'' && g.input[i] != 0)
					i++;
				if (g.input[i] == '\'')
				{
					t++;
					while(g.input[t] != '\'')
					{
						printf("%c", g.input[t]);
						t++;
					}
				}
				else
				{
					printf("error\n");
					return 0;
				}
				
			}
			else if (g.input[i] == '\"')
			{
				i ++;
				while(g.input[i] != '\"' && g.input[i] != 0)
					i++;
				if (g.input[i] == '\"')
				{
					while(g.input[++t] != '\"')
						printf("%c", g.input[t]);
				}
				else
				{
					printf("error\n");
					return 0;
				}
				
			}
		}
		else
			printf("%c", g.input[i]);
		i ++;
	}
	printf("\n");
	return 0;	
}
void ft_cd()
{

}
void ft_pwd()
{

}
void ft_export()
{

}
void ft_unset()
{

}