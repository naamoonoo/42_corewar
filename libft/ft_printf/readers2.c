/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:38:16 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 13:54:22 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*read_ptr(va_list ap)
{
	char **ptr;

	ptr = (char **)malloc(sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	*ptr = va_arg(ap, char *);
	return ((void *)ptr);
}

void	*read_double(va_list ap)
{
	double *l;

	l = malloc(sizeof(double));
	if (l == NULL)
		return (NULL);
	*l = va_arg(ap, double);
	return (l);
}

void	*read_longdouble(va_list ap)
{
	long double *l;

	l = malloc(sizeof(long double));
	if (l == NULL)
		return (NULL);
	*l = va_arg(ap, long double);
	return (l);
}
