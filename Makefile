NAME = containers

SRCS_VECTOR = vector_test.cpp
SRCS_STACK = stack_test.cpp
SRCS_MAP = map_test.cpp

VECTOR_DEP = ft.h map.h
STACK_DEP = ft.h map.h
MAP_DEP = ft.h map.h

VECTOR = vector
STACK = stack
MAP = map

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

OBJS_DIR =   .obj

OBJS_VECTOR =   $(addprefix $(OBJS_DIR)/, $(patsubst %.cpp, %.o, $(SRCS_VECTOR)))
OBJS_STACK	=	$(addprefix $(OBJS_DIR)/, $(patsubst %.cpp, %.o, $(SRCS_STACK)))
OBJS_MAP	=	$(addprefix $(OBJS_DIR)/, $(patsubst %.cpp, %.o, $(SRCS_MAP)))

all: all_vector all_stack all_map

all_vector: $(VECTOR)
all_stack: $(STACK)
all_map: $(MAP)

$(VECTOR): $(OBJS_VECTOR)
	clang++ $(CFLAGS) $(OBJS_VECTOR) -o $(VECTOR)

$(STACK): $(OBJS_STACK)
	clang++ $(CFLAGS) $(OBJS_STACK) -o $(STACK)

$(MAP): $(OBJS_MAP)
	clang++ $(CFLAGS) $(OBJS_MAP) -o $(MAP)

$(OBJS_DIR)/%.o:   %.cpp ft.h
	test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
	clang++ $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_VECTOR) $(OBJS_STACK) $(OBJS_MAP)

fclean: clean
	rm -rf $(VECTOR) $(STACK) $(MAP)

re: fclean all

.PHONY: all fclean re
.PHONY: SRCS NAME HEADER CC CFLAGS OBJS_DIR OBJS
