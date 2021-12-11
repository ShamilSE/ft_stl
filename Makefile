NAME = containers

UTILS_LIB = utils/libutils.a
UTILS_SRC = utils/libutils.c
UTILS_O = utils/libutils.o

VECTOR_TEST = tests/vector_test.cpp

SRC = main.cpp
#INC = vector.hpp SomeClass.hpp map.hpp stack.hpp
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

make_lib:
	gcc -g -c $(UTILS_SRC) -o $(UTILS_O)
	ar rc $(UTILS_LIB) $(UTILS_O)
	ranlib $(UTILS_LIB)

$(NAME): make_lib $(SRC) $(UTC)
	clang++ $(CFLAGS) $(SRC) $(VECTOR_TEST) -c
	clang++ main.o vector_test.o -L utils -lutils -o $(NAME)


fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean re
