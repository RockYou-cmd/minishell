#include "minishell.h"

void update_env(char *old,char *new)
{
	int i;
	char	*j_old;
	char	*j_new;

	i = 0;
	while (g.env[i])
	{
		if (!strncmp(g.env[i],"PWD=" , 4))
		{
			j_new = ft_strdup("PWD=");
			// free(g.env[i]);
			g.env[i] = ft_strjoin(j_new, new);
		}
		else if (!strncmp(g.env[i],"OLDPWD=" , 7))
		{
			j_old = ft_strdup("OLDPWD=");
			// free(g.env[i]);
			g.env[i] = ft_strjoin(j_old, old);
		}
		i++;
	}
}

int ft_echo(char **str)
{
	int i;

	i = 0;
	if (!str)
		printf("\n");
	while (ft_strcmp(str[0],"-e"))
		i++;
	while(str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	if (!ft_strcmp(str[0],"-e"))
		printf("\n");
	return(1);
}

void ft_cd(char **str)
{
	int		i;
	char	*path;
	char	old[1024];
	char	new[1024];

	getcwd(old, sizeof(old));
	if (!str)
	{
		i = 0;
		while (g.env[i])
		{
			if (!strncmp(g.env[i],"HOME=" , 5))
				path = g.env[i] + 5;
			i++;
		}
	}
	else
		path = str[0];
	if (chdir(path))
		printf("error command cd\n");
	getcwd(new, sizeof(new));
	update_env(old,new);
	// printf("old:%s\n",old);
	// printf("new:%s\n",new);
}

int ft_pwd()
{
	char a[1024];

	if (getcwd(a, sizeof(a)))
		printf("%s\n", a);
	else
	{
		printf("error command pwd\n");
		return (0);
	}
	return (1);
}
void ft_export(char **str)
{
	(void)str;
}
void ft_unset(char **str)
{
	(void)str;

}