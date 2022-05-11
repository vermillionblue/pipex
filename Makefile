# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 14:28:55 by danisanc          #+#    #+#              #
#    Updated: 2022/05/11 00:24:40 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = start.c

CC = gcc

CFLAGS = -Wextra -Wall -Werror -g

$(NAME): 
	$(CC) ${SRCS} libft/libft.a  -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re