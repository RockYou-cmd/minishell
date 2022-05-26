#include "minishell.h"

void ft_echo(char *str)
{
	if (!str)
		printf("\n");
	else
		printf("%s\n", str);
}
void ft_cd()
{

}
void ft_pwd()
{
	char *a = NULL;
	printf("%s\n", getcwd(a, sizeof(a)));
}
void ft_export()
{

}
void ft_unset()
{

}