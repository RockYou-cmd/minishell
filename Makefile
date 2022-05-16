# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 12:06:40 by rgatnaou          #+#    #+#              #
#    Updated: 2022/05/11 20:08:56 by ael-korc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = minishell.h 
LIBINC = libft/libft.h

INCLUDE_READLINE = -I /goinfre/ael-korc/.brew/opt/readline/include

LIB_READLINE = -L /goinfre/ael-korc/.brew/opt/readline/lib/ -lreadline

CC = cc -Wall -Wextra -Werror 

SRC = minishell.c exec.c parsing.c exec2.c libft/ft_strncmp.c

OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) -c $< -o $@

all : $(NAME)

$(NAME) : $(INC) $(LIBINC) $(OBJ)
	$(CC)  $(INCLUDE_READLINE) $(LIB_READLINE) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all