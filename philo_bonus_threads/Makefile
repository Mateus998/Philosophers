# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/06 11:39:17 by mateferr          #+#    #+#              #
#    Updated: 2025/10/06 16:29:45 by mateferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRC = src/utils.c src/process_utils.c src/init.c src/free_exits.c \
src/philos_process.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) philo.c -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all