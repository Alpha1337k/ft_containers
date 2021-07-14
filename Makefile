# .___________________________________________________________________________.
# |                                                                           |
# |     ____  ______   | Oscar Kruithof                                       |
# |    / __/ /__  __/  | https://github.com/Alpha1337k                        |
# |   / /=     / /     | okruitho                                             |
# |  /_/      /_/      |                                                      |
# | _________________________________________________________________________ |
# |       _                                                                   |
# |     /   )                                                                 |
# |    /       __    _   _/_   _    .   _     _     _      _                  |
# |   /      /   ) /   ) /   / - ) /  /   ) /  _) /   )  ( _ `                |
# |  ( __ / ( _ / /   / /   /   / /  /   / (     /  \`  \ _ )                 |
# |                                                                           |
# .___________________________________________________________________________.

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
