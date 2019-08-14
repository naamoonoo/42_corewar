FILL	=	hnam.filler
VISU	=	visualizer

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
#  -g -fsanitize=address

LIB		=	-L frameworks/SDL2.framework/lib -l SDL2 -L frameworks/SDL2_ttf.framework/lib -l SDL2_ttf
INCLUDE	=	-Iincludes -Iframeworks/SDL2.framework/includes/SDL2 -Iframeworks/SDL2_ttf.framework/includes

SRC		=	$(wildcard src/filler/*.c)
OBJ		=	$(patsubst src/filler/%.c, obj/filler/%.o, $(SRC))
SRC_V	=	$(wildcard src/visualizer/*.c)
OBJ_V	=	$(patsubst src/visualizer/%.c, obj/visualizer/%.o, $(SRC_V))

all		:	$(FILL) $(VISU)

obj/%.o	: 	src/%.c
			@$(CC) $(CFLAGS) $(OPTION) -c -o $@ $< $(INCLUDE)

$(FILL)	:	obj $(OBJ)
			@cd lib && make
			@mv lib/libftprintf.a .
			@$(CC) -o $(FILL) $(CFLAGS) $(OBJ) libftprintf.a
			@echo "excutable file $(FILL) has been made"

$(VISU)	:	obj $(OBJ_V)
			@cd lib && make
			@mv lib/libftprintf.a .
			@$(CC) -o $(VISU) $(CFLAGS) $(OBJ_V) libftprintf.a $(INCLUDE) $(LIB)
			@echo "excutable file $(VISU) has been made"

obj		:
			@mkdir obj
			@mkdir obj/filler
			@mkdir obj/visualizer

clean	:
			-cd lib && make clean
			-rm -rf obj

fclean	:	clean
			-rm -f $(FILL) $(VISU)
			-rm -f libftprintf.a

re		:	fclean $(FILL) $(VISU)

.PHONY	:	clean fclean re
