NAME=Schlacht
SRC_FOLDER=src/
SRC_FILES= main.cpp
SRC= $(addprefix $(SRC_FOLDER), $(SRC_FILES))

OBJ_DIR= obj/
INC_DIR= inc/
INC_F= $(addprefix $(INC_DIR), )
LIBS=-Llib -lraylib
INCL=-Iinc

OBJ= $(addprefix obj/, $(SRC_FILES:.cpp=.o))

TEST= src/test.cpp

FLAGS= -Wall -Wextra -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL


all: $(NAME)

prep :
	$(FLAGS) += -Werror -O3

final : prep all

$(NAME) : $(OBJ_DIR) $(OBJ)
	c++ $(INCL) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_FOLDER)%.cpp $(INC_F)
	c++ $(INCL) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
	rm -f test.out

fclean : clean
	rm -fr $(OBJ_DIR)
	rm -f $(NAME)

re : fclean all

test:
	c++ $(FLAGS) $(TEST) $(INCL) $(LIBS) -o test.out

$(OBJ_DIR) :
	mkdir obj

.PHONY: all clean fclean final prep 