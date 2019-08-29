/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 16:35:08 by aderby            #+#    #+#             */
/*   Updated: 2019/05/22 13:40:26 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <wchar.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# define PID print1->pid
# define FIELD_W print1->pid->fw
# define PFT (*print1)->type
# define PPID (*print1)->pid
# define F_ALT (*print1)->pid->f_alt
# define FF_ALT (*p)->pid->f_alt
# define UIM (*print1)->pid->fmt->uim
# define IM (*print1)->pid->fmt->im
# define NIM print1->pid->fmt->im
# define CONVERSIONS "sSpdDioOuUxXcCbB%"
# define NUM_CONVERSIONS "dDioOuUxXbB"
# define LENGTHS "hljz"
# define STRING_TYPE 0
# define S_TYPE 1
# define SS_TYPE 2
# define DI_TYPE 3
# define DD_TYPE 4
# define O_TYPE 5
# define OO_TYPE 6
# define U_TYPE 7
# define UU_TYPE 8
# define X_TYPE 9
# define XX_TYPE 10
# define C_TYPE 11
# define CC_TYPE 12
# define P_TYPE 13
# define PCNT_TYPE 14
# define B_TYPE 15
# define BB_TYPE 16
# define L_HH 0
# define L_H 1
# define L_L 2
# define L_LL 3
# define L_J 4
# define L_Z 5
# define SC_TYPE 20
# define UC_TYPE 21
# define SH_TYPE 22
# define USH_TYPE 23
# define L_TYPE 24
# define UL_TYPE 25
# define LL_TYPE 26
# define ULL_TYPE 27
# define IM_TYPE 28
# define UIM_TYPE 29
# define ST_TYPE 30
# define WC_TYPE 31
# define WS_TYPE 32
# define IS_DI(x) (x == DI_TYPE)
# define IS_SC(x) (x == SC_TYPE)
# define IS_SH(x) (x == SH_TYPE)
# define IS_L(x) (x == L_TYPE)
# define IS_LL(x) (x == LL_TYPE)
# define IS_IM(x) (x == IM_TYPE)
# define IS_SIGNED1(x) (IS_DI(x) || IS_SC(x) || IS_SH(x))
# define IS_SIGNED2(x) (IS_L(x) || IS_LL(x) || IS_IM(x))
# define IS_SIGNED(x) (IS_SIGNED1(x) || IS_SIGNED2(x))
# define IS_P(x) (x == P_TYPE)
# define IS_O(x) (x == O_TYPE)
# define IS_OO(x) (x == OO_TYPE)
# define IS_OOO(x) (x == O_TYPE || x == OO_TYPE)
# define IS_U(x) (x == U_TYPE)
# define IS_UU(x) (x == UU_TYPE)
# define IS_UUU(x) (x == U_TYPE || x == UU_TYPE)
# define IS_X(x) (x == X_TYPE)
# define IS_XX(x) (x == XX_TYPE)
# define IS_XXX(x) (x == X_TYPE || x == XX_TYPE)
# define IS_OUX(x) (IS_OOO(x) || IS_UUU(x) || IS_XXX(x))
# define IS_ST(x) (x == ST_TYPE)
# define IS_UC(x) (x == UC_TYPE)
# define IS_USH(x) (x == USH_TYPE)
# define IS_UL(x) (x == UL_TYPE)
# define IS_ULL(x) (x == ULL_TYPE)
# define IS_UIM(x) (x == UIM_TYPE)
# define IS_UNSIGNED1(x) (IS_OUX(x) || IS_ST(x) || IS_UC(x) || IS_USH(x))
# define IS_UNSIGNED2(x) (IS_UL(x) || IS_ULL(x) || IS_UIM(x) || IS_P(x))
# define IS_UNSIGNED(x) (IS_UNSIGNED1(x) || IS_UNSIGNED2(x))
# define IS_WI(x) (x == WI_TYPE)
# define IS_WC(x) (x == WC_TYPE)
# define IS_W(x) (IS_WI(x) || IS_WC(x))

typedef union		u_format
{
	int				c;
	char			*s;
	void			*p;
	wchar_t			wc;
	wchar_t			*ws;
	intmax_t		im;
	uintmax_t		uim;
}					t_format;

typedef struct		s_pid
{
	int				fw;
	int				prec;
	int				len;
	int				f_alt;
	int				f_zero;
	int				f_ladj;
	int				f_space;
	int				f_sign;
	int				base;
	int				xbase;
	union u_format	*fmt;
}					t_pid;

typedef struct		s_printf
{
	int				type;
	int				(*function)(struct s_printf *);
	char			*str;
	struct s_pid	*pid;
	struct s_printf	*next;
}					t_printf;

typedef struct		s_function
{
	int				(*f)(t_printf **, char *, int);
}					t_function;

size_t				ft_strlen(const char *s);
void				ft_putchar(const char c);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
char				*ft_strfresize(char **s, size_t newsize);
int					ft_iswhitespace(int c);
char				*ft_strfremalloc(char **s);
size_t				ft_putchars(const char c, size_t n);
char				*ft_strofchars(const char c, size_t num);
char				*ft_strffjoin(char **s1, char **s2);
void				ft_strdelthree(char **s, char **s2, char **s3);
void				ft_strdeltwo(char **s, char **s2);
void				ft_strtolower(char **s);
char				*ft_strfjoin(char **s1, const char *s2);
wchar_t				*ft_wstrdup(wchar_t *ws);
wchar_t				*ft_wstrnew(size_t len);
void				ft_putwchar(wchar_t wi);
wchar_t				*ft_wstrsub(wchar_t *ws, size_t start, size_t len);
size_t				ft_wstrlen(wchar_t *s);
int					num_of_bytes(unsigned int ui);
void				ft_putwstr(wchar_t *ws);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t n);
void				ft_putnbr(int n);
char				*ft_strnew(size_t size);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t len);
void				ft_strdel(char **as);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
long long			ft_atoll(const char *str);
char				*ft_strdup(const char *s1);
void				free_printf_fmt(t_format **fmt, int type);
void				free_printf_pid(t_pid **pid);
void				free_all(t_printf **head);
int					set_flags(t_printf **prtin1, char *s, int j);
int					set_fieldwidth(t_printf **print1, char *s, int j);
int					set_length(t_printf **print1, char *s, int j);
int					set_type(t_printf **print1, char *s, int j);
int					set_precision(t_printf **print1, char *s, int j);
int					ft_islengthchar(int c);
int					ft_isconversionchar(int c);
int					ft_isnumericconversionchar(int c);
int					pf_widechar(t_printf *print1);
int					pf_widestr(t_printf *print1);
int					pf_unsignedint(t_printf *print1);
int					pf_string(t_printf *print1);
int					pf_signedint(t_printf *print1);
int					pf_percent(t_printf *print1);
int					pf_character(t_printf *print1);
t_printf			*newlist(void);
int					storechar_prints(t_printf **print1, const char c, int ret);
void				readjust_percentid(t_printf **print1, char *s, int a);
void				initialize_function(t_function *function);
t_pid				*new_percentid(void);
int					set_uniondata(t_printf **print1, int type, va_list *args);
int					store_datafmt(t_printf **print1, va_list *args);
int					store_formatmods(t_printf **p, char *s, va_list *a, int r);
int					ft_printf(char *fmt, ...);

#endif
