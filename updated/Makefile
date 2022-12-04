NAME=Schlacht
VPATH    = src/ src/map src/ui src/units src/datastructure inc/ src/algorithm
SRC_FILES= main.cpp Tile.cpp Map.cpp Data.cpp Ui.cpp Unit.cpp \
           Parser.cpp BaseData.cpp Utils.cpp ObjectLayer.cpp \
           EventHandlerType.cpp GameObjects.cpp Scene.cpp \
           Player.cpp PathFinder.cpp ComPlayer.cpp

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
LIBS=-Llib
INCL=-Iinc -Imap -Iui -Iunits -Idatastructure -Ialgorithm

OBJ= $(addprefix $(OBJ_DIR), $(patsubst %.cpp, %.o, $(SRC)))

TEST= src/test.cpp

ifeq ($(OS), Windows_NT)
	#TODO
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		LDFLAGS += -lraylib-linux -lGL -lpthread -lm -ldl -lrt -lX11
	else ifeq ($(UNAME_S), Darwin)
		LDFLAGS += -Llib -lraylib-mac -lglfw3-mac -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
	endif
endif

FLAGS += -Wall -Wextra -std=c++17 -fsanitize=address


all: add_debug_flag $(NAME)

add_debug_flag:
	$(eval FLAGS+=-DDEBUG -g)

release: final $(NAME)

pipeline:
	sudo apt-get install --assume-yes --force-yes libglfw3-dev
	make -C .

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
