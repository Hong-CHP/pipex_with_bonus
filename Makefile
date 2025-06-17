# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 14:04:55 by hporta-c          #+#    #+#              #
#    Updated: 2025/06/17 14:13:37 by hporta-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = -gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = main.c pipex.c checker.c execute_pipex.c split_args.c utils_others.c \
		get_next_line.c get_next_line_utils.c utils.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all re