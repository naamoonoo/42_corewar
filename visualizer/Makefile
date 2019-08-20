VISU	=	visualizer

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

# for me to use
LIB		=	-L frameworks/SDL2.framework/lib -l SDL2 -L frameworks/SDL2_ttf.framework/lib -l SDL2_ttf
INCLUDE	=	-Iincludes -Iframeworks/SDL2.framework/includes/SDL2 -Iframeworks/SDL2_ttf.framework/includes

# for submit, need to brew install sdl2 / sdl2_ttf first
# LIB		=	-L ~/.brew/Cellar/sdl2/2.0.9_1/lib -l SDL2-2.0.0 -L ~/.brew/Cellar/sdl2_ttf/2.0.15/lib -l SDL2_ttf-2.0.0
# INCLUDE	=	-Iincludes -I~/.brew/Cellar/sdl2/2.0.9_1/includes/SDL2 -I~/.brew/Cellar/sdl2_ttf/2.0.15/includes/SDL2

SRC_V	=	$(wildcard src/visualizer/*.c)
OBJ_V	=	$(patsubst src/visualizer/%.c, obj/visualizer/%.o, $(SRC_V))

all		:	$(VISU)

obj/%.o	: 	src/%.c
			@$(CC) $(CFLAGS) $(OPTION) -c -o $@ $< $(INCLUDE)

$(VISU)	:	obj $(OBJ_V)
			@cd lib && make
			@mv lib/libftprintf.a .
			@$(CC) -o $(VISU) $(CFLAGS) $(OBJ_V) libftprintf.a $(INCLUDE) $(LIB)
			@echo "excutable file $(VISU) has been made"

obj		:
			@mkdir obj
			@mkdir obj/visualizer

clean	:
			-cd lib && make clean
			-rm -rf obj

fclean	:	clean
			-rm -f $(FILL) $(VISU)
			-rm -f libftprintf.a

re		:	fclean $(FILL) $(VISU)

.PHONY	:	clean fclean re
