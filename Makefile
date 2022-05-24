# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 20:22:30 by danisanc          #+#    #+#              #
#    Updated: 2022/05/24 00:08:06 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = main.c gnl/get_next_line.c gnl/get_next_line_utils.c ft_sttrjoin.c  errors.c  parse.c bonus.c

CC = gcc

CFLAGS = -Wextra -Wall -Werror

OBJS	= ${SRCS:.c=.o}

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(OBJS) libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	rm -f *.o
	rm -f libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re