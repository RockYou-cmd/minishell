#include "minishell.h"


void	get_path()
{
	int i;

	i = 0;
	while(g.env[i])
	{
		if (!ft_strncmp(g.env[i], "PATH=", 5))
			g.path = ft_split(g.env[i] + 5,':');
		i++;
	}
}

char	*get_bin(char *cmd)
{
	int i;
	char *bin;
	char *pat;

	i =0;
	if (!cmd)
		return(NULL);
	if (!access(cmd,X_OK))
		return(cmd);
	while (g.path[i])
	{
		pat = ft_strjoin(g.path[i],"/");
		bin = ft_strjoin(pat,cmd);
		free(pat);
		if (!access(bin,X_OK))
			return(bin);
		free(bin);
		i++;	
	}
	printf("*not\n");
	return(NULL);
}
int check_build_command(char *read, char *cmd)
{
	int	t;
	int	i;

	t = 0;
	i = 0;
	g.cmnd = -1;

	printf("check buil-%s-**\n",read);
	while(g.command[t] != 0)
	{
		if (ft_strcmp(cmd , g.command[t]) == 0)
		{
			g.cmnd = t;
			while (read[i] == ' ' && read[i] != '\0')
				i++;
			while (read[i] != ' ' && read[i] != '\0')
				i++;
			if (read[i] == ' ')
				i++;
			if (read[i] == '\0')
				which_one(NULL);
			else
				which_one(&read[i]);
			return(1);
		}    
		t++;
	}
	return(0);
}
void exec(char *read)
{
	int		pid;
	int		check;
	t_cmd	cmd;

	if (!read || !read[0])
		return;
	cmd.s_cmd = ft_split(read,' ');
	check = check_build_command(read, cmd.s_cmd[0]);
	if(check)
	{
		ft_free(cmd.s_cmd);
		free(read);
		return ;
	}
	cmd.bin = get_bin(cmd.s_cmd[0]);
	pid = fork();
	if(!pid)
	{
		execve(cmd.bin,cmd.s_cmd,g.env);
		write(2,"Command not fond \"", 18);
		write(2,cmd.s_cmd[0], ft_strlen(cmd.s_cmd[0]));
		write(2,"\"\n",2);
		ft_free(cmd.s_cmd);
		free(cmd.bin);
		free(read);
		exit(1);
	}
	wait(NULL);
}


// void exec_v2()
// {
// 	int	pid;
// 	int	pipefd[2];
// 	int d_stdin;
// 	t_cmd *cmd;	
// 	t_list *list;

// 	list = *g.list;
// 	pipe(pipefd);

// 	d_stdin = dup(0);
// 	while(list->next)
// 	{
// 		cmd = (t_cmd *)list->content;
// 		pid = fork();
// 		if(!pid)
// 		{
// 			printf("*bin: %s, cmd: %s\n", cmd->bin, cmd->s_cmd[0]);
// 			dup2(pipefd[1],1);
// 			close(pipefd[1]);
// 			close(pipefd[0]);
// 			execve(cmd->bin,cmd->s_cmd,g.env);
// 			write(2,"Command not fond \"", 18);
// 			if(cmd->s_cmd[0])
// 				write(2,cmd->s_cmd[0], ft_strlen(cmd->s_cmd[0]));
// 			write(2,"\"\n",2);
// 			exit(1);
// 		}
// 		dup2(pipefd[0],0);
// 		close(pipefd[1]);
// 		waitpid(pid, NULL, 0);
// 		list = list->next;
// 	}
// 	exec((t_cmd*) list->content);
// 	dup2(d_stdin, 0);
// }

void exec_v2(char *read)
{
	int	pid;
	int	pipefd[2];
	int		check = 0;
	t_cmd	cmd;
	pipe(pipefd);
	if (!read || !read[0])
		return;
	cmd.s_cmd = ft_split(read, ' ');
	check = check_build_command(read, cmd.s_cmd[0]);
	if(check)
	{
		ft_free(cmd.s_cmd);
		free(read);
		dup2(pipefd[0],0);
		close(pipefd[1]);
		return ;
	}
	printf("** -%s-   **\n",read);
	cmd.bin = get_bin(cmd.s_cmd[0]);
	pid = fork();
	if(!pid)
	{
		dup2(pipefd[1],1);
		close(pipefd[1]);
		close(pipefd[0]);
		execve(cmd.bin,cmd.s_cmd,g.env);
		write(2,"Command not fond \"", 18);
		if(cmd.s_cmd[0])
			write(2,cmd.s_cmd[0], ft_strlen(cmd.s_cmd[0]));
		write(2,"\"\n",2);
		exit(1);
	}
	dup2(pipefd[0],0);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
}
// void check_pipe()
// {
// 	t_list	*list;
// 	t_cmd	*cmd;
// 	char	**read;
// 	int		i;


// 	if (ft_strchr(g.input, '|'))
// 	{
// 		i = 0;
// 		read = ft_split(g.input, '|');
// 		while(read[i])
// 		{
// 			cmd = malloc(sizeof(t_cmd));
// 			cmd->s_cmd = ft_split(read[i], ' ');
// 			cmd->bin = get_bin(cmd->s_cmd[0]);
// 			ft_lstadd_back(&list,ft_lstnew(cmd));
// 			i++;
// 		}
// 		g.list = &list;
// 		exec_v2();
// 	}
	// else
	// {
	// 	g.cmd = malloc(sizeof(t_cmd));
	// 	g.cmd->s_cmd = ft_split(g.input, ' ');
	// 	get_path();
	// 	g.cmd->bin = get_bin(g.cmd->s_cmd[0]);
	// 	exec(g.cmd);
	// }
// }