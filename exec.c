#include "minishell.h"

int ft_echo(char **str)
{
	int i;
	i = 0;
	if (!str || !str[0])
	{
		printf("\n");
		return (1);
	}
	while(str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
	return(1);
}
void ft_cd()
{

}
void ft_pwd()
{
	char *a = NULL;
	printf("%s\n", getcwd(a, sizeof(a)));
}
void ft_exit()
{
	
}

void ft_env()
{

}