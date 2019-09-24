CC=gcc
CFLAGS=-Wall -Wextra -Werror
export CC
export CFLAGS
OBJS_LIBC=ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
		  ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o \
		  ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o \
		  ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o \
		  ft_atoi.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o \
		  ft_isprint.o ft_toupper.o ft_tolower.o
OBJS_EXTRA=ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o \
		   ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o \
		   ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o \
		   ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o \
		   ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o
OBJS_BONUS=ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o \
		   ft_lstmap.o
OBJS_PERSONAL=ft_abs.o ft_itoa_base.o ft_itoa_base_u.o ft_lstappend.o \
			  ft_make_lowercase.o ft_make_uppercase.o ft_max.o ft_memdup.o \
			  ft_min.o ft_pop_atoi.o ft_strlcpy.o ft_strndup.o ft_strrev.o \
			  ft_strsum.o ft_swapbytes.o ft_number_cpy.o \
			  ft_memrev.o ft_convert_endian.o ft_left_rotate.o \
			  ft_right_rotate.o ft_putstr_upper.o ft_putstr_lower.o \
			  ft_strchri.o ft_file_processor.o \
			  ft_arrlst_new.o ft_arrlst_add.o ft_arrlst_clear.o \
			  ft_arrlst_indexof.o ft_arrlst_remove.o ft_arrlst_iter.o \
			  ft_arrlst_del.o ft_arrlst_isempty.o ft_arrlst_get.o \
			  ft_arrlst_remove_last.o ft_arrlst_contains.o \
			  ft_arrlst_add_arrlst.o ft_arrlst_add_arr.o ft_arrlst_set.o \
			  ft_iswhite.o ft_strcmpi.o ft_strequi.o ft_error.o \
			  get_file.o ft_strjoin_by.o ft_strsplits.o
OBJS=$(OBJS_LIBC) $(OBJS_EXTRA) $(OBJS_BONUS) $(OBJS_PERSONAL)
PROJ_GNL=get_next_line.o
PROJ_PRINTF_SRC=$(wildcard ft_printf/*.c)
PROJ_PRINTF=$(PROJ_PRINTF_SRC:.c=.o)
AR=ar rcs
RM=rm -rf
NAME=libft.a

$(NAME): $(OBJS) $(PROJ_GNL) $(PROJ_PRINTF)
	$(AR) $(NAME) $(OBJS) $(PROJ_GNL) $(PROJ_PRINTF)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(PROJ_GNL)
	$(RM) $(PROJ_PRINTF)
	$(RM) $(wildcard *.gch)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(PROJ_GNL): get_next_line.h
