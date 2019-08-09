/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:38:16 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 13:54:10 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*read_char(va_list ap)
{
	char *c;

	c = malloc(sizeof(char));
	if (c == NULL)
		return (NULL);
	*c = (char)va_arg(ap, int);
	return (c);
}

void	*read_short(va_list ap)
{
	short *s;

	s = malloc(sizeof(short));
	if (s == NULL)
		return (NULL);
	*s = (short)va_arg(ap, int);
	return (s);
}

void	*read_int(va_list ap)
{
	int *i;

	i = malloc(sizeof(int));
	if (i == NULL)
		return (NULL);
	*i = va_arg(ap, int);
	return (i);
}

void	*read_long(va_list ap)
{
	long *l;

	l = malloc(sizeof(long));
	if (l == NULL)
		return (NULL);
	*l = va_arg(ap, long);
	return (l);
}

void	*read_longlong(va_list ap)
{
	long long *l;

	l = malloc(sizeof(long long));
	if (l == NULL)
		return (NULL);
	*l = va_arg(ap, long long);
	return (l);
}
