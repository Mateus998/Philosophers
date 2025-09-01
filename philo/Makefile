# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/12 11:17:05 by mateferr          #+#    #+#              #
#    Updated: 2025/09/01 17:20:09 by mateferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = src/utils.c src/utils2.c src/philo_rotine.c src/init.c src/state_rotine.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) philosophers.c -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all