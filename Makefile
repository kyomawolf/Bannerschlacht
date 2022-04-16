NAME=Schlacht
SRC= mainloop.cpp unit.cpp board.cpp
OBJ_DIR= obj/
INC_DIR= inc/
INC_F= $(addprefix $(INC_DIR), board.hpp unit.hpp)
LIBS= -lraylib
INCL=-Iinc
OBJ= $(addprefix $(OBJ_DIR), $(patsubst %.cpp,%.o, $(SRC)))
FLAGS= -Wall -Wextra 


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
	mkdir obj

.PHONY: all clean fclean final prep 