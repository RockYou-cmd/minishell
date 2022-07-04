# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/07 11:36:40 by rgatnaou          #+#    #+#              #
#    Updated: 2022/07/04 21:21:10 by ael-korc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

HEADER = libft.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC =   ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_memcmp.c		\
		ft_memset.c		\
		ft_strlen.c		\
		ft_strnstr.c	\
		ft_tolower.c	\
		ft_bzero.c		\
		ft_isalpha.c	\
		ft_isdigit.c	\
		ft_memchr.c		\
		ft_memcpy.c		\
		ft_strchr.c		\
		ft_strlcpy.c	\
		ft_strncmp.c	\
		ft_strrchr.c	\
		ft_toupper.c	\
		ft_strlcat.c	\
		ft_memmove.c	\
		ft_atoi.c		\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_putnbr_fd.c	\
		ft_putchar_fd.c	\
		ft_itoa.c		\
		utils.c			\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_split2.c		\
		ft_striteri.c	\
		ft_strcmp.c
		

SRC_B = ft_lstnew.c		\
		ft_lstadd_front.c	\
		ft_lstsize.c	\
		ft_lstlast.c	\
		ft_lstadd_back.c	\
		ft_lstdelone.c	\
		ft_lstclear.c	\
		ft_lstiter.c	\
		ft_lstmap.c

OBJECTS = $(SRC:.c=.o)
OBJECTS_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	ar -rcs $(NAME) $(OBJECTS) 

bonus : $(OBJECTS) $(OBJECTS_B)  $(HEADER)
	ar -rcs $(NAME) $(OBJECTS) $(OBJECTS_B)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJECTS) $(OBJECTS_B) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

