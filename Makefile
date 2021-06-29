# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: alpha <alpha@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/15 00:20:06 by alpha         #+#    #+#                  #
#    Updated: 2021/06/29 12:36:05 by alpha         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=ft_containers

CC=clang++
FLAGS=-Wall -Werror -Wextra
DEBUG_FLAGS=-g
SRC=main.cpp test/*.cpp
HEADERS=src/*.hpp
LIBS=-I src/
OBJ=
RM =rm -rf

all: $(NAME)

$(NAME): $(SRC) $(HEADERS)
	$(CC) $(FLAGS) $(SRC) $(LIBS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

os:
	$(CC) $(FLAGS) $(SRC) $(LIBS) -D USE_OS_VARIANT=1 -o $(NAME)_native

run: re
	./$(NAME)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(SRC) $(LIBS) -o $(NAME)
