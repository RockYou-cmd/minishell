#include "minishell.h"


void	get_path()
{
	int i;

	i = 0;
	while(g.env[i])
	{
		if (!ft_strncmp(g.env[i], "PATH=", 5))
			g.cmd->path = ft_split(g.env[i] + 5,':');
		i++;
	}
}

void	get_bin()
{
	int i;
	char *bin;
	char *pat;

	i = 0;
	if (!access(g.cmd->s_cmd[0],X_OK))
	{
		g.cmd->bin = g.cmd->s_cmd[0];
		return;
	}
	while (g.cmd->path[i])
	{
		pat = ft_strjoin(g.cmd->path[i],"/");
		bin = ft_strjoin(pat,g.cmd->s_cmd[0]);
		free(pat);
		if (!access(bin,X_OK))
		{
			g.cmd->bin = bin;
			return;
		}
		free(bin);
		i++;	
	}
}

void exec()
{
	// t_list	*list;
	// char	**read;
	// int		i;
	int		pid;
	// if (ft_strchr(g.input, '|'))
	// {
	// 	i = 0;
	// 	read = ft_split(g.input, '|');
	// 	while(read[i])
	// 	{
	// 		cmd->cmd = ft_split(read[i], ' ');
	// 		cmd->path = get_path(g.env);
	// 		cmd->bin = get_bin(cmd->cmd,cmd->path);
	// 		ft_lstadd_back(&list,ft_lstnew(cmd));
	// 		i++;
	// 	}
	// 	printf("your are loser\n");
	// }
	// g.list = &list;
	pid = fork();
	if(!pid)
	{
		execve(g.cmd->bin,g.cmd->s_cmd ,g.env);
		printf("bin: %s, cmd: %s. \n", g.cmd->bin,g.cmd->s_cmd[0] );
		write(2,"Command not fond \"", 18);
		if(g.cmd->s_cmd[0])
			write(2,g.cmd->s_cmd[0], ft_strlen(g.cmd->s_cmd[0]));
		write(2,"\"\n",2);
		exit(1);
	}
	wait(NULL);
}