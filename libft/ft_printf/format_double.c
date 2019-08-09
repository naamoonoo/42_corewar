/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:52:30 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 14:59:11 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "float.h"

void	free_exact_float(t_exact_float *f)
{
	free(f->integer.value);
	free(f->fraction.value);
	free(f->integer_str);
	free(f->fraction_str);
	free(f);
}

char	*format_double(t_printable *p)
{
	t_exact_float	*f;
	char			*str;

	if (p->modifier == MOD_LD)
		f = longdouble_to_exact_float(*(long double *)p->data);
	else
		f = double_to_exact_float(*(double *)p->data);
	if (f == NULL)
		return (NULL);
	str = format_special(f, p->flags);
	if (!str)
	{
		if (p->type == 'e' || p->type == 'E')
			str = format_e(f, p);
		else if (p->type == 'f' || p->type == 'F')
			str = format_f(f, p);
	}
	if (!str)
		return (NULL);
	if (p->type >= 'a' && p->type <= 'z')
		ft_make_lowercase(str);
	else
		ft_make_uppercase(str);
	free_exact_float(f);
	return (str);
}
