# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 15:32:55 by danisanc          #+#    #+#              #
#    Updated: 2022/05/24 00:08:53 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#target: dependencies
#	action

#targets ...: target-pattern: prereq-patterns ...
#   commands

NAME= libft.a

CC= gcc

CFLAGS= -Wall -Wextra -Werror

SRCS= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_memchr.c \
ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strncmp.c \
ft_atol.c

OBJS= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $@ $^

all: $(NAME)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: clean all

.PHONY : clean re fclean
