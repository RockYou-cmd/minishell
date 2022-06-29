#include "minishell.h"
void	create_pwd(int	s, int i, char *pwd, char *old_pwd)
{
	char 	**env;
	int  j;

	i = 0;
	while(g.env[i++]);
	env = malloc((i + 3) * sizeof(char *));
	j = 0;
	i = 0;
	while (g.env[i])
	{
		if (j == 10 && (s == 1 || !s) )
			env[j++] = pwd;
		else if (j == 5 && ( s == 2 || !s))
			env[j++] = old_pwd;
		else
			env[j++] = strdup(g.env[i++]);
	}
	env[j] = 0;
	ft_free(g.env);
	g.env = env;
}

void update_pwd(char *old,char *new)
{
	int 	i;
	int 	s;
	char	*pwd;
	char	*old_pwd;

	i = 0;
	s = 0;
	pwd =  ft_strjoin(ft_strdup("PWD="), new);
	old_pwd = ft_strjoin(ft_strdup("OLDPWD="), old);
	while (g.env[i])
	{
		if (!strncmp(g.env[i],"PWD=" , 4))
		{
			free(g.env[i]);
			g.env[i] = pwd;
			s += 2;
		}
		else if (!strncmp(g.env[i],"OLDPWD=" , 7))
		{
			free(g.env[i]);
			g.env[i] = old_pwd;
			s += 1;
		}
		i++;
	}
	if (s == 0 || s < 3)
		create_pwd(s, i, pwd, old_pwd);
}

int ft_echo(char **str)
{
	int i;
	int j;
	int s;

	s = 0;
	i = 0;
	if (!str || !str[0])
	{
		printf("\n");
		return(0);
	}
	while (str[i] && !ft_strncmp(str[i],"-n",2))
	{
		j = 1;
		while(str[i][j] == 'n')
			j++;
		if (str[i][j] != '\0')
			break;
		else if (i == 0)
			s = -1;
		i++;
	}
	while(str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	if (s != -1)
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
	if (!str || !str[0])
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
    if(!g.env)
		return (1);
    while (g.env[i])
    {
        if (ft_strchr(g.env[i],'='))
            printf("%s\n",g.env[i]);
        i++;
    }
	return (0);
}
