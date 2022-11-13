NAME=Schlacht
VPATH    = src/ src/map src/ui src/units src/datastructure
SRC_FILES= main.cpp Tile.cpp Map.cpp Data.cpp Ui.cpp Unit.cpp \
           Parser.cpp BaseData.cpp Utils.cpp ObjectLayer.cpp \
           EventHandlerType.cpp GameObjects.cpp Scene.cpp \
           Player.cpp

DEP_FILES= AudioDevice.hpp \
           AudioStream.hpp \
           BoundingBox.hpp \
           Camera2D.hpp \
           Camera3D.hpp \
           Color.hpp \
           Font.hpp \
           Functions.hpp \
           Gamepad.hpp \
           Image.hpp \
           Material.hpp \
           Matrix.hpp \
           Mesh.hpp \
           Model.hpp \
           ModelAnimation.hpp \
           Mouse.hpp \
           Music.hpp \
           physac.hpp \
           Physics.hpp \
           Ray.hpp \
           RayCollision.hpp \
           raylib.hpp \
           raylib-cpp.hpp \
           raylib-cpp-utils.hpp \
           RaylibException.hpp \
           raymath.hpp \
           Rectangle.hpp \
           RenderTexture.hpp \
           Shader.hpp \
           Sound.hpp \
           Text.hpp \
           Texture.hpp \
           Vector2.hpp \
           Vector3.hpp \
           Vector4.hpp \
           VrStereoConfig.hpp \
           Wave.hpp \
           Window.hpp #tile.hpp map.hpp data.hpp
SRC= $(SRC_FILES)

OBJ_DIR= obj/
INC_DIR= inc/
INC_F= $(addprefix $(INC_DIR), $(DEP_FILES))
LIBS=-Llib -lraylib #-lGL -lpthread -lm -ldl -lrt -lX11
INCL=-Iinc

OBJ= $(addprefix $(OBJ_DIR), $(patsubst %.cpp, %.o, $(SRC)))

TEST= src/test.cpp

ifeq ($(OS), Windows_NT)
	#TODO
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		LDFLAGS +=
	else ifeq ($(UNAME_S), Darwin)
		LDFLAGS += -Llib -lglfw3 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
	endif
endif

FLAGS= -Wall -Wextra -std=c++17


all: add_debug_flag $(NAME)

add_debug_flag:
	$(eval FLAGS+=-DDEBUG)

release: final $(NAME)

final :
	$(eval FLAGS+=-Werror -O3)

$(NAME) : $(OBJ_DIR) $(OBJ)
	c++ $(INCL) $(FLAGS) $(OBJ) $(LIBS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: %.cpp #$(INC_F) #$(SRC_FOLDER)$(DEP_FILES)
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
