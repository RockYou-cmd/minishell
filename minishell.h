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

#ifndef	MINISHELL_H
#define	MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>

typedef struct s_cmd
{
	char	**s_cmd;
	char	*bin;
}t_cmd;

typedef struct s_data
{
	char 		*command[8];
	char 		*input;
	int 		cmnd;
	int			pip;
	t_cmd		*cmd;
	char		**env;
	char		**s_env;
	t_list	 	**list;
	char		**path;
	char		*clr_cmd;
	int			i_stdin;
	int			i_stdout;
	int			fd_stdin;
	int			fd_stdout;
	int			i;
	int			t;
	pid_t		pid_ch;
}t_data;

t_data g;
 
void	comands();
void	which_one(char **str);
void 	ft_init();
int		ft_echo(char **str);
void	ft_cd();
void	ft_pwd();
void	ft_export();
void	ft_unset();
void 	check();
void	ft_env();
void	ft_exit();
void	get_path();
char	*get_bin(char *cmd);
void	exec(char **cmd);
void	exec_v2(char **read);
void	ft_free(char **s_cmd);
char	*v_env(char *str);
int 	dolar(char *str, int s);
void    ft_heredoc();
char 	**esp_splt(char *str);
void 	red_output(char **str);
void 	ooc(char c, int *s, int *d);
int 	red_check(char *str);
void 	red_send(char *str);
void find_red(char **str, int i);
void	exec_heredoc(char *limeter);
int 	red(char *str);
void exec_red_output_append(char *file);
void exec_red_output(char *file);
void handler(int signm);

#endif