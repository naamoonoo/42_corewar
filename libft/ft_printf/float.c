/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:55:08 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/18 18:07:54 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "float.h"

static void	check_specials(t_float *f)
{
	if (f->exponent == -1023)
	{
		if (f->significand)
			f->exponent = -1022;
		else
			f->type = 'z';
	}
	else if (f->exponent == 1024)
	{
		if (f->significand)
			f->type = 'n';
		else
			f->type = 'i';
	}
	else
		f->significand |= (long)1 << 52;
}

static void	check_long_specials(t_float *f)
{
	if (f->exponent == -16383)
	{
		if (f->significand)
			f->exponent = -16382;
		else
			f->type = 'z';
	}
	else if (f->exponent == 16384)
	{
		if (f->significand & 0x7fffffffffffffff)
			f->type = 'n';
		else
			f->type = 'i';
	}
}

t_float		*parse_double(double d)
{
	char	*data;
	t_float	*f;

	f = (t_float *)malloc(sizeof(t_float));
	if (!f)
		return (NULL);
	data = (char *)(void *)&d;
	f->type = 'd';
	f->sign = ((data[7] & 0x80) >> 7) ? -1 : 1;
	f->exponent = (*((short *)(data + 6)) & 0x7fff) >> 4;
	f->exponent -= 1023;
	f->significand = *((long *)data) & 0xfffffffffffff;
	check_specials(f);
	return (f);
}

t_float		*parse_longdouble(long double d)
{
	char	*data;
	t_float	*f;

	f = (t_float *)malloc(sizeof(t_float));
	if (!f)
		return (NULL);
	data = (char *)(void *)&d;
	f->type = 'l';
	f->sign = ((data[9] & 0x80) >> 7) ? -1 : 1;
	f->exponent = *((short *)(data + 8)) & 0x7fff;
	f->exponent -= 16383;
	f->significand = *(long *)data;
	check_long_specials(f);
	return (f);
}

void		del_float(t_float **f)
{
	free(*f);
	*f = NULL;
}
