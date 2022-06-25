# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgatnaou <rgatnaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 12:06:40 by rgatnaou          #+#    #+#              #
#    Updated: 2022/05/16 20:58:48 by rgatnaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = minishell.h 

LIBINC = libft/libft.h

LIBFT = libft/libft.a

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)

READLINE = $(shell brew --prefix readline)

CC = cc -Wall -Wextra -Werror

SRC = minishell.c exec.c parsing.c exec2.c exec3.c Sys_Cmd.c init.c utils.c redirection_pars.c redirection_find.c check.c

OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) -I $(INCLUDE_READLINE) -c $< -o $@

all : $(NAME)

$(NAME) : $(INC) $(LIBINC) $(LIBFT) $(OBJ)
	$(CC)  -I $(INCLUDE_READLINE) -L $(LIB_READLINE) -lreadline $(LIBFT) $(OBJ) -o $(NAME)

$(LIBFT)	:
	make bonus -C libft

clean :
	rm -rf $(OBJ)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean all