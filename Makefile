NAME=Schlacht
CRYSTAL_SRC= crystal/core.cpp
SRC= main.cpp unit.cpp mainloop.cpp board.cpp soldier.cpp
OBJ_DIR= obj/
INC_DIR= inc/
INC_F= $(addprefix $(INC_DIR), board.hpp unit.hpp)
LIBS=-Llib -lraylib
INCL=-Iinc
OBJ= $(addprefix obj/, $(CRYSTAL_SRC:.cpp=.o))  $(addprefix obj/, $(SRC:.cpp=.o)) 
FLAGS= -Wall -Wextra -std=c++20 -fmodules-ts


all: $(NAME)

prep :
	$(FLAGS) += -Werror -O3

final : prep all

$(NAME) : $(OBJ_DIR) $(OBJ) 
	c++ $(INCL) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o : %.cpp $(INC_F)
	c++ $(INCL) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -fr $(OBJ_DIR)
	rm -f $(NAME)

re : fclean all

$(OBJ_DIR) :
	mkdir obj obj/crystal

.PHONY: all clean fclean final prep 