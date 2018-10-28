NAME        = avm
CXX         = g++
CXXFLAGS    = -Wall -Wextra -pedantic -std=c++11 -g -O0

OBJ_DIR    = obj/
INC_DIR    = inc/
SRC_DIR    = src/

FILES  = OperandFactory Instruction Lexer VirtualMachine TOperand Parser main

OBJ        = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES) ) )
HEADERS    = $(addsuffix .hpp, $(FILES))

INCLUDES    = -I $(INC_DIR)

VPATH += src/

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $< $(INCLUDES)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
