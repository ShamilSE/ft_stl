NAME = containers
SRC = tests/stack_test.cpp main.cpp
INC = vector.hpp SomeClass.hpp map.hpp stack.hpp
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

all: $(NAME)

$(NAME): $(SRC) $(INC)
	clang++ $(CFLAGS) $(SRC) -o $(NAME)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean re
