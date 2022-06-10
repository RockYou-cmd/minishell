
#include "minishell.h"

int    len_heredoc(char **heredoc)
{
    int i;
    int c;

    i = 0;
    c = 0;
    while (heredoc[i])
    {
        while (heredoc[i] && ft_strcmp(heredoc[i],"<<"))
        {
            c++;
            i++;
        }
        i+=2;
        while (heredoc[i] && ft_strcmp(heredoc[i],"<<"))
        {
            c++;
            i++;
        }
    }
    return (c);
}

void	exec_heredoc(char *limeter, char **cmd)
{
	int		i;
	int		fd;
	char	*doc;

	if (limeter)
		fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
    i = 0;
    while(i >= 0 && limeter)
    {
        doc = readline("> ");
        if (!doc)
        {
            write(1, "\033[1A> ",6);
            break;    
        }
        if (!ft_strcmp(limeter,doc))
            break;
        write(fd, doc, ft_strlen(doc));
        write(fd , "\n", 1);
        i++;
		free(doc);
    }
	if (!limeter)
	{
		close(fd);
		fd = open(".heredoc", O_RDWR, 0644);
		dup2(fd , 0);
		exec(cmd);
		dup2(g.i_stdin , 0);
		close(fd);
	}
}

void    ft_heredoc(char **str)
{
	int i;
	int j;
	int t;
	char **cmd;
	char **tmp;


	i = 0;
	j = 0;
	t = 0;
	tmp = esp_splt(*str);
	cmd = calloc(len_heredoc(ft_split(g.input, ' ')) + 1 ,sizeof(char *));
	while (tmp[i])
	{
		cmd[j++] = tmp[i++];
	}
	i = 0;
	while (str[++i] != 0)
	{
		t = 0;
		tmp = esp_splt(str[i]);
		exec_heredoc(tmp[t], cmd);
		while (tmp[++t])
			cmd[j ++] = tmp [t];
	}
	exec_heredoc(NULL, cmd);
	cmd[j] = 0;
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
		if (ft_strcmp(cmd[0] , g.command[t]) == 0)
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
	// printf("cmd last : %s\n",cmd.bin);
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