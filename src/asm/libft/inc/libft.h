/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:54:27 by aderby            #+#    #+#             */
/*   Updated: 2019/08/22 15:39:14 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ft_printf.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
long long			ft_atoll(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_iswhitespace(int c);
int					ft_abs(int a);
int					ft_sign(int a);

char				*ft_strtrim(char const *s);
char				*ft_strctrim2(char const *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *big, const char *little, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnew(size_t size);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnjoin(char const *s1, char const *s2, char *s3);
char				*ft_strjoinf(char *s1, char *s2);
char				*ft_strwjoin(char **s, char *c);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_itoa(int n);
char				*ft_find_n_replace(char *s, char f, char r, int n);
char				*ft_split_whitespace(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplits(char *s, char *c);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_striter(char *s, void (*f)(char *));
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(intmax_t n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(const char *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar(char c);
void				ft_strclr(char *s);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_bzero(void *s, size_t n);
void				ft_strrev(char *str);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memchr(const void *s, int c, size_t n);

size_t				ft_strlen(const char *str);
size_t				ft_arrlen(char **str);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

char				**ft_arraynew(int width, int height);
char				***ft_4darraynew(int width, int height, int depth);
char				*ft_strctrim(char *str, char c, int i);

#endif
