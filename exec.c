#include "minishell.h"

void update_pwd(char *old,char *new)
{
	int 	i;

	i = 0;
	while (g.env[i])
	{
		if (!strncmp(g.env[i],"PWD=" , 4))
		{
			free(g.env[i]);
			g.env[i] = ft_strjoin(ft_strdup("PWD="), new);
		}
		else if (!strncmp(g.env[i],"OLDPWD=" , 7))
		{
			free(g.env[i]);
			g.env[i] = ft_strjoin(ft_strdup("OLDPWD="), old);
		}
		i++;
	}
}

int ft_echo(char **str)
{
	int i;

	i = 0;
	if (!str || !str[0])
		printf("\n");
	while (str[i] && !ft_strncmp(str[i],"-n",2))
		i++;
	while(str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	if (ft_strncmp(str[0],"-n",2))
		printf("\n");
	return(0);
}

int ft_cd(char **str)
{
	int		i;
	char	*path;
	char	old[1024];
	char	new[1024];

	path = 0;
	getcwd(old, sizeof(old));
	if (!str)
	{
		i = -1;
		while (g.env[++i])
			if (!strncmp(g.env[i],"HOME=" , 5))
				path = g.env[i] + 5;
	}
	else
		path = str[0];
	if (chdir(path))
	{
		printf("cd: %s: No such file or directory\n",path);
		return (1);
	}
	getcwd(new, sizeof(new));
	update_pwd(old,new);
	return (0);
}

int ft_pwd()
{
	char a[1024];

	if (getcwd(a, sizeof(a)))
		printf("%s\n", a);
	else
	{
		printf("error command pwd\n");
		return (1);
	}
	return (0);
}

void ft_exit()
{
	
}

int ft_env()
{
    int i = 0;
    
    while (g.env[i])
    {
        if (ft_strchr(g.env[i],'='))
            printf("%s\n",g.env[i]);
        i++;
    }
	return (0);
}
