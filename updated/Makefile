NAME=Schlacht
RAYWRAP=
SRC_FOLDER=src/
SRC_FILES=
SRC= $(addprefix $(SRC_FOLDER), $(SRC_FILES))
OBJ_DIR= obj/
INC_DIR= inc/
INC_F= $(addprefix $(INC_DIR), )
LIBS=-Llib -lraylib
INCL=-Iinc
OBJ= $(addprefix obj/, $(RAYWRAP:.cpp=.o))  $(addprefix obj/, $(SRC_FILES):.cpp=.o))
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
	mkdir obj obj/crystal

.PHONY: all clean fclean final prep 