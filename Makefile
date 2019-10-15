CC=gcc
CFLAGS=-Wall -Wextra -Werror
RM=rm -rf

VISU_LIB=-L ~/.brew/Cellar/sdl2/2.0.9_1/lib -l SDL2-2.0.0 -L ~/.brew/Cellar/sdl2_ttf/2.0.15/lib -l SDL2_ttf-2.0.0
VISU_INCLUDE=-Iincludes -I $(HOME)/.brew/Cellar/sdl2/2.0.9_1/include/SDL2 -I $(HOME)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2

SRC_DIR=src/
BIN_DIR=bin/
TEST_DIR=test/

ASM_OBJS=$(addprefix $(BIN_DIR),\
		 identify_arg_type.o parse_name_comment.o parse_tree.o asm.o parse_utils.o parser.o write_name_comment.o dasm.o write_to_file.o decode.o write_utils.o edit_indirect_value.o parse_indirect_values.o error.o parse_instruction_line.o extension_check.o parse_instruction_params.o global.o parse_label.o tree_search.o)
VM_OBJS=$(addprefix $(BIN_DIR), mem.o scheduler.o purge_list.o mem_block.o process.o decode_arg_list.o arg_list_io.o vm.o champion.o valid_arg_list.o read_arg_number.o build_champions.o free_champ.o create_visualizer.o \
		in_live.o in_ld.o in_add.o in_sub.o \
		in_st.o in_and.o in_or.o in_xor.o \
		in_zjmp.o in_ldi.o in_lld.o in_lldi.o \
		in_fork.o in_lfork.o in_aff.o in_sti.o \
		in_lt.o in_gt.o in_aa.o \
		visualizer_text_1.o visualizer_text_2.o visualizer_text_3.o)
VISUALIZER_OBJS=$(addprefix $(BIN_DIR), visualizer_sdl1.o visualizer_sdl2.o visualizer_sdl3.o visualizer_sdl4.o helper.o init.o play1.o play2.o start1.o start2.o itoa_base.o)
COMMON_OBJS=$(addprefix $(BIN_DIR), op.o)
TEST_OBJS=$(addprefix $(BIN_DIR), test_mem.o test_scheduler.o test_mem_block.o test_process.o test_decode_arg_list.o \
		  test_in_live.o test_in_ld.o test_in_add.o test_in_sub.o \
		  test_in_st.o test_in_and.o test_in_or.o test_in_xor.o \
		  test_in_zjmp.o test_in_ldi.o test_in_lld.o test_in_lldi.o \
		  test_in_fork.o test_in_lfork.o test_in_sti.o)
ALL_OBJS=$(ASM_OBJS) $(VM_OBJS) $(COMMON_OBJS) $(TEST_OBJS)

NAME_ASM=asm
NAME_VM=corewar

################ EXECUTABLES ################

all: $(NAME_VM) $(NAME_ASM)

$(BIN_DIR)asm_main.o: $(SRC_DIR)asm/main.c
	$(CC) $(CFLAGS) -c $< -o $@ -I include -I libft

$(BIN_DIR)vm_main.o: $(SRC_DIR)vm/main.c
	$(CC) $(CFLAGS) -c $< -o $@ $(VISU_INCLUDE)

$(NAME_ASM): $(ASM_OBJS) $(COMMON_OBJS) $(BIN_DIR)asm_main.o -lft
	$(CC) $(CFLAGS) $(ASM_OBJS) $(COMMON_OBJS) $(BIN_DIR)asm_main.o -o $(NAME_ASM) -L $(LIBFT) -lft

$(NAME_VM): $(VM_OBJS) $(VISUALIZER_OBJS) $(COMMON_OBJS) $(BIN_DIR)vm_main.o -lft
	$(CC) $(CFLAGS) $(VM_OBJS) $(VISUALIZER_OBJS) $(COMMON_OBJS) $(BIN_DIR)vm_main.o -o $(NAME_VM) -L $(LIBFT) -lft $(VISU_LIB)

################ LIBFT ################

LIBFT=libft/
vpath libft.a $(LIBFT)

$(LIBFT)libft.a:
	make -C $(LIBFT)

################ OBJECTS ################

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(ASM_OBJS): $(BIN_DIR)%.o: $(SRC_DIR)asm/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I include -I libft $(VISU_INCLUDE)

$(VM_OBJS): $(BIN_DIR)%.o: $(SRC_DIR)vm/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(VISU_INCLUDE)

$(VISUALIZER_OBJS): $(BIN_DIR)%.o: $(SRC_DIR)visualizer/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(VISU_INCLUDE)

$(COMMON_OBJS): $(BIN_DIR)%.o: $(SRC_DIR)%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJS): $(BIN_DIR)test_%.o: $(TEST_DIR)%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(CHECKPATH)include

################ TESTING (DEPRECATED) ################
#
#CHECKPATH=~/.brew/Cellar/check/0.12.0/
#
#$(BIN_DIR)check_all.o: $(TEST_DIR)check_all.c | $(BIN_DIR)
#	mkdir -p $(BIN_DIR)
#	$(CC) $(CFLAGS) -c $(TEST_DIR)check_all.c -o $(BIN_DIR)check_all.o -I $(CHECKPATH)include
#
#check_all: $(BIN_DIR)check_all.o $(ALL_OBJS) $(TEST_OBJS) -lft
#	$(CC) $(CFLAGS) $(BIN_DIR)check_all.o $(ALL_OBJS) -L $(CHECKPATH)lib -lcheck -lm -lpthread -L $(LIBFT) -lft -o check_all

################ PHONY ################

.PHONY: all clean fclean re check norme

clean:
	$(RM) $(OBJS)
	$(RM) $(TEST_OBJS)
	$(RM) $(BIN_DIR)
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME_ASM)
	$(RM) $(NAME_VM)
	$(RM) check_all
	make -C $(LIBFT) fclean

re: fclean all

#check: check_all
#	./check_all

norme:
	norminette libft/*.[ch]
	norminette libft/ft_printf/*.[ch]
	norminette include/
	norminette src/op.c
	norminette src/asm/
	norminette src/vm/
	norminette src/visualizer/*.[ch]
