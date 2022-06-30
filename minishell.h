/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:08 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/05/20 12:50:52 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>

typedef struct s_data
{
	char		*command[8];
	char		*input;
	char		*file;
	int			cmnd;
	int			pip;
	char		**s_cmd;
	char		**env;
	char		**path;
	char		*clr_cmd;
	int			i_stdin;
	int			i_stdout;
	int			fd_stdin;
	int			fd_stdout;
	int			state;
	int			i;
	int			t;
	pid_t		pid_ch;
	int			pipefd[2];
}t_data;

t_data	g;

void	comands(void);
void	which_one(char **str);
int		ft_init(void);
int		ft_echo(char **str);
int		ft_cd(char **str);
int		ft_pwd(void);
int		ft_export(char **str);
void	ft_unset(char **str);
void	check(void);
int		ft_env(void);
void	ft_exit(void);
char	*get_bin(char *cmd);
void	exec(char **cmd);
void	exec_v2(char **read);
void	ft_free(char **s_cmd);
char	*v_env(char *str);
int		dolar(char *str, int s);
void	ft_heredoc(void);
char	**esp_splt(char *str);
void	red_output(char **str);
void	ooc(char c, int *s, int *d);
int		red_check(char *str);
void	red_send(char *str, int pipe);
void	find_red(char **str, int i, int *pipe);
void	exec_heredoc(char *limeter);
int		red(char *str);
void	exec_red_output_append(char *file, int *pipe);
void	exec_red_output(char *file, int *pipe);
void	handler(int signm);
void	exec_red_input(char *file);
char	**ft_realloc(char **str, int t);
void	fill_export(void);
char	*ft_rrealloc(char *str, int t);
int		exp_sign(char **str);
int		is_iq(char *str, int j);
void	exp_to_env(void);

#endif