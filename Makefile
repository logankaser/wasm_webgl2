NAME = index
LIST_CPP = main \
GLWindow \
Input \
ShadingProgram \
Rectangle \
Texture \
TextureFactory \
Client \
Player \
Socket \
Entity \
EntityManager \
Renderable \
game_protocol.pb

LIST_JS = raster

OBJ_DIR = obj

VPATH = src:src/js:src/networking

SRC = $(addsuffix .cpp, $(LIST_CPP))
OBJ = $(addsuffix .bc, $(addprefix $(OBJ_DIR)/, $(LIST_CPP)))
DEP = $(OBJ:%.bc=%.d)

SRC_JS = $(addsuffix .js, $(LIST_JS))
OBJ_JS = $(addsuffix .min.js, $(addprefix $(OBJ_DIR)/, $(LIST_JS)))

CC = em++
INCLUDES = -I ~/.brew/include -I src/ -I . $(shell pkg-config --cflags protobuf-lite)

MAKEFLAGS=-j4

CPPFLAGS = -Wall -Wextra -Werror -O3 -std=c++17 $(INCLUDES)

#OPT = --llvm-lto 3 -O3 --closure 1

LDFLAGS = $(OPT) -s WASM=1 -s USE_WEBGL2=1 --pipe \
--preload-file bundle \
-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
--js-library src/js/library_raster.js --pre-js obj/raster.min.js \
 -pthread

all: src/networking/game_protocol.pb.cpp $(OBJ_DIR) $(NAME).wasm

$(NAME).wasm: $(OBJ) $(OBJ_JS) $(OBJ_DIR)/libprotobuf-lite.a
	@printf "\e[32;1mLinking.. \e[0m\n"
	@$(CC) $(LDFLAGS) $(OBJ) $(OBJ_DIR)/libprotobuf-lite.a -o $(NAME).js
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.bc: %.cpp
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	@$(CC) $(CPPFLAGS) -MMD -c $< -o $@

$(OBJ_DIR)/%.min.js: %.js
	@printf "\e[36;1mCompiling: \e[0m%s\n" $<
	@closure-compiler --language_in ECMASCRIPT_2016 $< --js_output_file $@

# Protobuf stuff

src/networking/game_protocol.pb.cpp: game_protocol.proto
	@printf "\e[35;1mCompiling: \e[0m%s\n" $^
	@protoc $^ --cpp_out=.
	@mv src/networking/game_protocol.pb.cc src/networking/game_protocol.pb.cpp
	@printf "\e[32;1mCreated:\e[0m %s\n" $@

$(OBJ_DIR)/libprotobuf-lite.a: lib/libprotobuf-lite.a.gz
	@printf "\e[35;1mExtracting: \e[0m%s\n" $^
	@gunzip -k $^
	@mv lib/libprotobuf-lite.a $@

clean:
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -f $(OBJ) $(DEP)

fclean:
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME).js $(NAME).wasm $(NAME).data

run: all
	python3 -m http.server 8080

re:
	@$(MAKE) fclean 2>/dev/null
	@$(MAKE) 2>/dev/null

.PHONY: clean fclean all re
