# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 17:41:20 by rpadasia          #+#    #+#              #
#    Updated: 2025/10/09 18:05:17 by rpadasia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread -p -fsanitize=thread

SRC_DIR	= srcs/
OBJ_DIR	= objs/

SRC		= main.c cleanup.c create_threads.c exception.c\
			initialize.c monitor.c monitorutils.c routine.c\
			routineutils.c utils1.c validity.c\

SRCS	= $(addprefix $(SRC_DIR), $(SRC))
OBJS	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean