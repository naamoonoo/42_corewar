/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exact_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 20:25:37 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/17 18:11:11 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exact_float.h"
#include "float.h"

static unsigned int		*clone_integer(unsigned int *arr, int size, int resize)
{
	unsigned int	*newarr;
	int				i;

	if (resize <= 0)
		return (NULL);
	newarr = malloc(resize * sizeof(int));
	if (!newarr)
		return (NULL);
	i = 0;
	while (i < resize)
	{
		if (i < size)
			newarr[resize - 1 - i] = arr[i];
		else
			newarr[resize - 1 - i] = 0;
		i++;
	}
	return (newarr);
}

static unsigned int		*clone_fraction(unsigned int *arr, int size, int resize)
{
	unsigned int	*newarr;
	int				i;

	if (resize <= 0)
		return (NULL);
	newarr = malloc(resize * sizeof(int));
	if (!newarr)
		return (NULL);
	i = 0;
	while (i < resize)
	{
		if (i >= resize - size)
			newarr[i] = arr[i + size - resize];
		else
			newarr[i] = 0;
		i++;
	}
	return (newarr);
}

static t_exact_float	*tfloat_to_exact_float(t_float *f)
{
	t_exact_float	*ef;
	int				exp;
	int				shift;
	unsigned int	sig[3];

	exp = f->exponent;
	shift = (exp >= 0) ? exp % 32 : (exp % 32) + 32;
	sig[0] = (unsigned int)(f->significand >> 32 >> (32 - shift));
	sig[1] = (unsigned int)(f->significand >> (32 - shift));
	sig[2] = (unsigned int)(f->significand << shift);
	exp = (exp - shift) / 32;
	ef = (t_exact_float *)malloc(sizeof(t_exact_float));
	if (!ef)
		return (NULL);
	ef->integer.size = exp + 3;
	ef->fraction.size = 0 - exp;
	if (ef->integer.size < 0)
		ef->integer.size = 0;
	if (ef->fraction.size < 0)
		ef->fraction.size = 0;
	ef->integer.value = clone_integer(sig, 3, ef->integer.size);
	ef->fraction.value = clone_fraction(sig, 3, ef->fraction.size);
	return (ef);
}

t_exact_float			*double_to_exact_float(double d)
{
	t_exact_float	*ef;
	t_float			*f;

	f = parse_double(d);
	if (f)
	{
		f->exponent -= 52;
		ef = tfloat_to_exact_float(f);
		if (ef)
		{
			ef->integer_str = NULL;
			ef->fraction_str = NULL;
		}
		ef->type = f->type;
		ef->sign = f->sign;
		del_float(&f);
		return (ef);
	}
	return (NULL);
}

t_exact_float			*longdouble_to_exact_float(long double d)
{
	t_exact_float	*ef;
	t_float			*f;

	f = parse_longdouble(d);
	if (f)
	{
		f->exponent -= 63;
		ef = tfloat_to_exact_float(f);
		if (ef)
		{
			ef->integer_str = NULL;
			ef->fraction_str = NULL;
		}
		ef->type = f->type;
		ef->sign = f->sign;
		del_float(&f);
		return (ef);
	}
	return (NULL);
}
