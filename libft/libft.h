/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:45:30 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/08/30 21:17:44 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HMODULUS 101

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const void *s, int c);
char				*ft_strrchr(const void *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *hay, const char *need, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstappend(t_list *alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int					ft_min(int a, int b);
int					ft_max(int a, int b);
char				*ft_strndup(const char *s1, int len);
void				ft_swapbytes(char *a, char *b);
void				ft_strrev(char *str);
char				*ft_strsum(const char *s1, const char *s2);
char				*ft_itoa_base_u(unsigned long long n, const char *base);
char				*ft_itoa_base(long long n, const char *base);
long long			ft_abs(long long n);
void				ft_make_lowercase(char *str);
void				ft_make_uppercase(char *str);
int					ft_pop_atoi(char *str);
void				*ft_memdup(void *src, size_t size);
void				*ft_number_cpy(void *dst, void *src, int size, int endian);
void				ft_memrev(void *mem, size_t len);
void				ft_convert_endian(void *data, int size, int sub_size);
unsigned int		ft_left_rotate(unsigned int n, int dist);
unsigned int		ft_right_rotate(unsigned int n, int dist);
void				ft_putstr_upper(char const *s);
void				ft_putstr_lower(char const *s);
int					ft_strchri(const void *s, int c);
int					ft_iswhite(char c);
int					ft_strcmpi(const char *s1, const char *s2);
int					ft_strequi(char const *s1, char const *s2);
int					ft_error(char *str, int i);

typedef struct		s_arrlst
{
	void			*data;
	size_t			elem_size;
	int				alloc_size;
	int				size;
}					t_arrlst;

t_arrlst			*ft_arrlst_new(int datum_size);
void				*ft_arrlst_add(t_arrlst *arrlst, void *new);
void				ft_arrlst_clear(t_arrlst *arrlst);
int					ft_arrlst_indexof(t_arrlst *arrlst, void *elem);
int					ft_arrlst_remove(t_arrlst *arrlst, void *elem);
void				ft_arrlst_iter(t_arrlst *arrlst, void (*f)(void *elem));
void				ft_arrlst_del(t_arrlst **arrlst);
int					ft_arrlst_isempty(t_arrlst *arrlst);
void				*ft_arrlst_get(t_arrlst *arrlst, int index);
void				ft_arrlst_remove_last(t_arrlst *arrlst, int amount);
typedef t_arrlst	t_arst;
void				*ft_arrlst_add_arrlst(t_arst *l, t_arst *s, int o, int a);
void				*ft_arrlst_add_arr(t_arrlst *arrlst, void *src, int amount);
int					ft_arrlst_contains(t_arrlst *arrlst, void *elem);
void				ft_arrlst_remove_last(t_arrlst *arrlst, int amount);
void				*ft_arrlst_set(t_arrlst *list, int index, void *data);

int					get_next_line(const int fd, char **line);

int					ft_printf(const char *format, ...);
int					ft_fdprintf(int fd, const char *format, ...);
char				*ft_strprintf(const char *format, ...);

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

int					get_file(int fd, char **file);
char				*ft_strjoin_by(char const *s1, char const *s2, char *c);
char				**ft_strsplits(char *s, char *c);

#endif
