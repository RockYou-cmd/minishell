
#include "minishell.h"

void	exec_heredoc(char *limeter)
{
	char	*doc;
	// int fd[2];
	
		g.fd_stdin = open("/tmp/.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	g.pid_ch = fork();
	if(!g.pid_ch)
	{
		signal(SIGINT, SIG_DFL);
		while(limeter)
		{
			doc = readline("> ");
			if (!doc)
			{
				write(1, "\033[1A> ",6);
				break;    
			}
			if (ft_strcmp(limeter,doc))
			break;
			write(g.fd_stdin, doc, ft_strlen(doc));
			write(g.fd_stdin , "\n", 1);
			free(doc);
		}
		exit(0);
	}
	waitpid(g.pid_ch, NULL, 0);
	g.pid_ch = 1337;
	close(g.fd_stdin);
	g.fd_stdin = open("/tmp/.heredoc", O_RDWR, 0644);
}

void exec_red_output(char *file, int *pipe)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return;
	if(g.fd_stdout != 1)
		close(g.fd_stdout);
	*pipe = 0;
	g.fd_stdout = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void exec_red_output_append(char *file, int *pipe)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return;
	if(g.fd_stdout != 1)
		close(g.fd_stdout);
	*pipe = 0;
	g.fd_stdout = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
}
void exec_red_input(char *file)
{
	if (g.fd_stdin == -1 || g.fd_stdout == -1)
		return;
	if (g.fd_stdin != 0)
		close(g.fd_stdin);
	g.fd_stdin = open(file, O_RDWR , 0644);

}
void	get_path()
{
	int i;

	i = 0;
	if (!g.env)
	{
		g.env = malloc(sizeof(char *)*2);
		g.env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
		g.env[1] = 0;
	}
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
		return(ft_strdup(cmd));
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

	t = 0;
	g.cmnd = -1;
	while(g.command[t] != 0)
	{
		if (ft_strcmp(cmd[0] , g.command[t]))
		{
			g.cmnd = t;
			which_one(&cmd[1]);
			ft_free(cmd);
			return(1);
		}    
		t++;
	}
	return(0);
}
void exec(char **s_cmd)
{
	int		check;
	char 	*bin;

	if (!s_cmd  || !s_cmd [0])
		return;
	check = check_build_command(s_cmd);
	if(check)
		return ;
	bin = get_bin(s_cmd[0]);
	g.pid_ch = fork();
	if(!g.pid_ch)
	{
		signal(SIGINT, &handler);
		execve(bin,s_cmd,g.env);
		write(2,"minishell: ", 11);
		write(2,s_cmd[0], ft_strlen(s_cmd[0]));
		write(2,": command not found\n",20);
		exit(1);
	}
	ft_free(s_cmd);
	free(bin);
	waitpid(g.pid_ch , &(g.state), 0);
}

void exec_v2(char **s_cmd)
{
	int		check;
	char 	*bin;

	write(2, "exec2\n", 6);
	pipe(g.pipefd);
	if (!s_cmd || !s_cmd[0])
		return;

	bin = get_bin(s_cmd[0]);
	g.pid_ch = fork();
	if(!g.pid_ch)
	{
		dup2(g.pipefd[1],1);
		close(g.pipefd[1]);
		close(g.pipefd[0]);
		check = check_build_command(s_cmd);
		if(check)
		{
			dup2(g.pipefd[0],0);
			close(g.pipefd[1]);
			exit(1);
		}
		execve(bin,s_cmd,g.env);
		write(2,"minishell :", 11);
		write(2,s_cmd[0], ft_strlen(s_cmd[0]));
		write(2,": command not found\n",20);
		exit(1);
	}
	ft_free(s_cmd);
	free(bin);
	dup2(g.pipefd[0],0);
	close(g.pipefd[1]);
	close(g.pipefd[0]);
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