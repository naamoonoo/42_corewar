/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfuncs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:00:57 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 00:44:47 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

char	*ft_strfresize(char **s, size_t newsize)
{
	char	*tmp;

	if (!(tmp = ft_strnew(newsize)))
		return (NULL);
	ft_strcpy(tmp, *s);
	ft_strdel(s);
	return (tmp);
}

int		ft_iswhitespace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r' ||
			c == '\f')
		return (1);
	return (0);
}

char	*ft_strfremalloc(char **s)
{
	char	*new;

	if (!(new = ft_strdup(*s)))
		return (NULL);
	free(*s);
	*s = NULL;
	return (new);
}

size_t	ft_putchars(const char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

char	*ft_strofchars(const char c, size_t num)
{
	char	*new;
	size_t	i;

	if (!(new = ft_strnew(num)))
		return (NULL);
	i = 0;
	while (i < num)
	{
		new[i] = c;
		i++;
	}
	new[i] = '\0';
	return (new);
}
