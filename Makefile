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
NAME_MAP=map_consitancy_test
NAME_SCHOOL=school_test


CC=clang++
FLAGS=-Wall -Werror -Wextra -Ofast
DEBUG_FLAGS=-g
SRC=main.cpp test/*.cpp
SRC_SCHOOL=schoolmain.cpp
SRC_MAP=map_consitancy.cpp
HEADERS=src/*.hpp
LIBS=-I src/
OBJ=
RM =rm -rf

all: $(NAME) $(NAME_MAP) $(NAME_SCHOOL)

$(NAME): $(SRC) $(HEADERS)
	$(CC) $(FLAGS) $(SRC) $(LIBS) -o $(NAME)

$(NAME_MAP): $(SRC_MAP) $(HEADERS)
	$(CC) $(FLAGS) $(SRC_MAP) $(LIBS) -o $(NAME_MAP)

$(NAME_SCHOOL): $(SRC_SCHOOL) $(HEADERS)
	$(CC) $(FLAGS) $(SRC_SCHOOL) $(LIBS) -o $(NAME_SCHOOL)
	$(CC) $(FLAGS) $(SRC_SCHOOL) $(LIBS) -D USE_STL=1 -o $(NAME_SCHOOL)_stl

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(NAME_MAP) $(NAME_SCHOOL) $(NAME_SCHOOL)_stl

re: fclean all

os:
	$(CC) $(FLAGS) $(SRC) $(LIBS) -D USE_OS_VARIANT=1 -o $(NAME)_native

run: re
	./$(NAME)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(SRC) $(LIBS) -o $(NAME)
