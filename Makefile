NAME = index
LIST = main \
GLWindow \
Input \
ShadingProgram \
Rectangle \
Texture

OBJ_DIR = obj

VPATH = src

SRC = $(addsuffix .cpp, $(LIST))
OBJ = $(addsuffix .bc, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.bc=%.d)
CC = em++
SUB =
INCLUDES=-I ~/.brew/include

CPPFLAGS = -Wall -Wextra -Werror -O3 -std=c++17 $(INCLUDES)

OPT = --llvm-lto 3 -O3 --closure 1

LDFLAGS = $(OPT) -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s USE_WEBGL2=1 \
--preload-file assets \
-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1

all: $(OBJ_DIR) $(NAME).wasm

$(NAME).wasm: $(OBJ)
	@for s in $(SUB);\
	do\
		make -sC $$s;\
	done
	@printf "\e[32;1mLinking.. \e[0m\n"
	@$(CC) $(LDFLAGS) $^ -o $(NAME).js
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.bc: %.cpp
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	@$(CC) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	@for s in $(SUB);\
	do\
		make -sC $$s clean;\
	done
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -f $(OBJ) $(DEP)

fclean:
	@for s in $(SUB);\
	do\
		make -sC $$s fclean;\
	done
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME).js $(NAME).wasm $(NAME).data

run: all
	python3 -m http.server 8080

re:	fclean all

.PHONY: clean fclean all re
