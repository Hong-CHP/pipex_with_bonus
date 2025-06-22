# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 14:04:55 by hporta-c          #+#    #+#              #
#    Updated: 2025/06/22 10:05:23 by hporta-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = pipex.c checker.c execute_pipex.c split_args.c utils.c utils_others.c
SRCS_BONUS = pipex_bonus.c checker_bonus.c pipex_pipe_bonus.c here_doc_bonus.c \
			execute_pipex_bonus.c split_args_bonus.c utils_others_bonus.c \
			utils_bonus.c get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
		$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all re