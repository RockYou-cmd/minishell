/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:52:08 by rgatnaou          #+#    #+#             */
/*   Updated: 2022/05/11 16:22:11 by rgatnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define	MINISHELL_H
#include<stdio.h>
#include "libft/libft.h"
#include<unistd.h>
#include<stddef.h>
#include<string.h>
#include<signal.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef struct s_data
{
	char *command[8];
	char *input;
	int cmnd;
}t_data;

t_data g;
 
void comands();
void check();
void which_one(int i);
int ft_echo(int i);
void ft_cd();
void ft_pwd();
void ft_export();
void ft_unset();
void ft_env();
void ft_exit();


#endif