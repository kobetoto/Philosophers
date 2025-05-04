# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 14:55:14 by thodavid          #+#    #+#              #
#    Updated: 2025/05/04 09:06:05 by thodavid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
## ARGUMENTS / VARIABLES

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
SRC_DIR		= srcs
OBJ_DIR		= objs

################################################################################
## SOURCES

SRCS		= 	main.c utils.c parsing.c thread.c

SRC_PATHS	= main.c $(addprefix $(SRC_DIR)/, parsing.c thread.c utils.c)

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

################################################################################
## REGLES

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/main.o:	main.c
			@mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
