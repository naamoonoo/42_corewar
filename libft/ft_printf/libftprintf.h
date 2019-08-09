/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:49:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/30 20:52:48 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft.h"
# include "argsize.h"
# include "readers.h"
# include "sizers.h"
# include "exact_float.h"

# define MOD_H 1
# define MOD_HH 2
# define MOD_L 3
# define MOD_LL 4
# define MOD_LD 5

# define BOOL char
# define ARG 1
# define NOT_ARG 0

# define ALTFORM 0x01
# define ZEROPAD 0x02
# define RIGHTPAD 0x04
# define SIGNSPACE 0x08
# define SIGNFORCE 0x10
# define DELIMITERS 0x20

typedef struct	s_argument
{
	ARGSIZE		type;
	void		*data;
}				t_argument;

typedef struct	s_arglist
{
	int			size;
	t_argument	**args;
	int			index;
}				t_arglist;

typedef struct	s_printable
{
	char		flags;
	int			field_width_arg;
	int			field_width;
	int			precision_arg;
	int			precision;
	char		modifier;
	char		type;
	int			data_arg;
	void		*data;
}				t_printable;

t_list			*new_printable(void);
t_list			*read_format_string(const char *format);
int				read_placeholder(const char **format, t_list *printables);
void			put_printable(t_list *printable);
void			free_printables(t_list **printables);

int				positional_args(t_list *printables);

t_arglist		*new_arglist(void);
int				set_arg_type(t_arglist *arglist, int index, ARGSIZE type);
void			free_arglist(t_arglist **arglist);
t_arglist		*build_arglist(t_list *printables, int positional);
int				withdraw_args(t_arglist *arglist, va_list ap);
void			inject_args(t_list *printables, t_arglist *arglist, int pstnl);

typedef void	*(*t_reader)(va_list);
typedef ARGSIZE	(*t_sizer)(char modifier);
typedef char	*(*t_formatter)(t_printable *);

typedef struct	s_type_reader
{
	ARGSIZE		size;
	t_reader	reader;
}				t_type_reader;

typedef struct	s_type_formatter
{
	char		type;
	t_sizer		sizer;
	t_formatter	formatter;
}				t_type_formatter;

static const t_type_reader g_type_readers[] =
{
	(t_type_reader) {SIZE_CHAR, &read_char},
	(t_type_reader) {SIZE_SHORT, &read_short},
	(t_type_reader) {SIZE_INT, &read_int},
	(t_type_reader) {SIZE_LONG, &read_long},
	(t_type_reader) {SIZE_LONGLONG, &read_longlong},
	(t_type_reader) {SIZE_DOUBLE, &read_double},
	(t_type_reader) {SIZE_LONGDOUBLE, &read_longdouble},
	(t_type_reader) {SIZE_PTR, &read_ptr},
	(t_type_reader) {0, 0}
};

char			*format_char(t_printable *p);
char			*format_str(t_printable *p);
char			*format_percent(t_printable *p);
char			*format_hexadecimal(t_printable *p);
char			*format_pointer(t_printable *p);
char			*format_octal(t_printable *p);
char			*format_unsigned_decimal(t_printable *p);
char			*format_decimal(t_printable *p);
char			*format_double(t_printable *p);
char			*format_non_printable(t_printable *p);

int				is_zero(t_exact_float *n);
int				round_up_check(char **str);
char			*format_e(t_exact_float *n, t_printable *p);
char			*format_f(t_exact_float *n, t_printable *p);
char			*format_special(t_exact_float *n, char flags);

static const t_type_formatter	g_type_formatters[] =
{
	(t_type_formatter) {'c', &size_char, &format_char},
	(t_type_formatter) {'d', &size_int, &format_decimal},
	(t_type_formatter) {'e', &size_double, &format_double},
	(t_type_formatter) {'E', &size_double, &format_double},
	(t_type_formatter) {'f', &size_double, &format_double},
	(t_type_formatter) {'F', &size_double, &format_double},
	(t_type_formatter) {'i', &size_int, &format_decimal},
	(t_type_formatter) {'o', &size_int, &format_octal},
	(t_type_formatter) {'p', &size_ptr, &format_pointer},
	(t_type_formatter) {'r', &size_ptr, &format_non_printable},
	(t_type_formatter) {'\1', &size_ptr, &format_str},
	(t_type_formatter) {'s', &size_ptr, &format_str},
	(t_type_formatter) {'u', &size_int, &format_unsigned_decimal},
	(t_type_formatter) {'x', &size_int, &format_hexadecimal},
	(t_type_formatter) {'X', &size_int, &format_hexadecimal},
	(t_type_formatter) {'%', NULL, &format_percent},
	(t_type_formatter) {0, 0, 0}
};

ARGSIZE			size_of_type(char type, char modifier);
t_reader		reader_for_size(ARGSIZE size);
t_reader		reader_for_type(char type, char modifier);
t_formatter		formatter_for_type(char type);
char			*num_prefix(char flags, int negative);
int				pad_left(char **str, size_t width);
char			*pad_printable(t_printable *p, const char *r, const char *str);
char			*pad_number(t_printable *p, const char *sign, const char *str);

int				ft_printf(const char *format, ...);
char			*ft_strprintf(const char *format, ...);

#endif
