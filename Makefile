# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 12:06:40 by rgatnaou          #+#    #+#              #
#    Updated: 2022/07/04 16:00:04 by ael-korc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = minishell.h 

LIBINC = libft/libft.h

LIBFT = libft/libft.a

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)

READLINE = $(shell brew --prefix readline)

CC = cc -Wall -Wextra -Werror #-static-libsan -fsanitize=address

SRC = minishell.c exec.c parsing.c exec2.c utils_export.c Sys_Cmd.c init.c utils.c expend.c \
		redirection_pars.c redirection_find.c pipe.c check.c redirection_execution.c \
		get_next_line.c

OBJ = $(SRC:.c=.o)

%.o : %.c $(INC) $(LIBINC)
	$(CC) -I $(INCLUDE_READLINE) -c $< -o $@

all : $(NAME)

$(NAME) : $(INC) $(LIBINC) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -I $(INCLUDE_READLINE)  -L $(LIB_READLINE)  $(LIBFT) -o $(NAME) -lreadline

$(LIBFT)	:
	make bonus -C libft

clean :
	rm -rf $(OBJ)
	make clean -C libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean all