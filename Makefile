# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcruz-an <rcruz-an@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 14:19:21 by rcruz-an          #+#    #+#              #
#    Updated: 2024/06/03 13:15:16 by rcruz-an         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c init.c threads.c monitor.c routine_actions.c
OBJ = $(SRC:.c=.o)
MANPATH = $(addprefix ./src/, $(SRC))
OBJP = $(addprefix ./src/, $(OBJ))

FLAGS = -Wall -Wextra -Werror -O3 -pthread
HEADER = ./src/philo.h

#SANITIZER = -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJP)
	cc $(FLAGS) -o $(NAME) $(OBJP) $(SANITIZER)

./src/%.o: ./src/%.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJP)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: FLAGS += -g
debug: re

.PHONY: all clean fclean re debug