#include "minishell.h"

// void checker(int i)
// {
// 	int q;

// 	q = 0;
// 	while(g.input[i] != 0)
// 	{
// 		if (g.input[i] == '\'' || g.input[i] == '\"')
// 		[
// 			if (g.input[i] == '\'')
			
// 		]
// 	}
// }

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
				while(g.input[i] != '\'')
					i++;
				if (g.input[i] == '\'')
				{
					while(g.input[++t] != '\'')
						printf("%c", g.input[t]);
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
				while(g.input[i] != '\"')
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