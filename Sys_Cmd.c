
#include "minishell.h"

void	exec_heredoc(char *limeter)
{
	// int		i;
	// char	*doc;

	// if (limeter)
	// 	g.fd_stdin = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
    // i = 0;
    // while(i >= 0 && limeter)
    // {
    //     doc = readline("> ");
    //     if (!doc)
    //     {
    //         write(1, "\033[1A> ",6);
    //         break;    
    //     }
    //     if (ft_strcmp(limeter,doc))
    //        break;
    //     write(g.fd_stdin, doc, ft_strlen(doc));
    //     write(g.fd_stdin , "\n", 1);
    //     i++;
	// 	free(doc);
    // }
	// // if (!limeter)
	// // {
	// 	close(g.fd_stdin);
	// 	g.fd_stdin = open(".heredoc", O_RDWR, 0644);
	// 	dup2(g.fd_stdin , 0);
	// // 	exec(cmd);

	// 	close(fd);
	// }
}

// void redirection_pars(char **str)
// {
// 	int j;
// 	int i;

// 	j = 0;
// 	i = 0;
// 	while (str[j])
// 	{
		
// 		while(str[j])
// 	}
// }


void exec_red_output(char *folder, char **cmd, int i)
{
	int		fd;

	fd = open(folder, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!i)
	{
		while (cmd[i])
			printf("cmd : %s\n", cmd[i++]);
		dup2(fd , 1);
		exec(cmd);
		dup2(g.i_stdout , 1);
	}
	close (fd);
}

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
		pat = ft_strdup(g.path[i]);
		pat = ft_strjoin(pat,"/");
		bin = ft_strjoin(pat,cmd);
		if (!access(bin,X_OK))
			return(bin);
		free(bin);
		i++;	
	}
	return(NULL);
}
int check_build_command(char **cmd)
{
	int	t;
	int	i;

	t = 0;
	i = 1;
	g.cmnd = -1;

	while(g.command[t] != 0)
	{
		if (ft_strcmp(cmd[0] , g.command[t]))
		{
			g.cmnd = t;
			if (!cmd[1])
			{
				which_one(NULL);
				return (1);
			}
			i++;
			if (cmd[1] != NULL)
			{
				which_one(&cmd[1]);
				return(1);
			}
		}    
		t++;
	}
	return(0);
}
void exec(char **read)
{
	int		pid;
	int		check;
	t_cmd	cmd;
	// int i =0;

	// while (read[i])
	// {
	// 	printf("%s ",read[i++]);
	// }
	if (!read || !read[0])
		return;
	cmd.s_cmd = read;
	check = check_build_command(cmd.s_cmd);
	if(check)
	{
		ft_free(cmd.s_cmd);
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
		exit(1);
	}
	wait(NULL);
}

void exec_v2(char **read)
{
	int	pid;
	int	pipefd[2];
	int		check = 0;
	t_cmd	cmd;
	pipe(pipefd);
	if (!read || !read[0])
		return;
	cmd.s_cmd = read;
	check = check_build_command(cmd.s_cmd);
	if(check)
	{
		ft_free(cmd.s_cmd);
		dup2(pipefd[0],0);
		close(pipefd[1]);
		return ;
	}
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