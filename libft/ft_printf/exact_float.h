/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exact_float.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 20:12:54 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/19 15:10:16 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXACT_FLOAT_H
# define EXACT_FLOAT_H

# include <stdlib.h>

typedef struct		s_big_integer
{
	unsigned int	*value;
	int				size;
}					t_big_integer;

typedef struct		s_big_fraction
{
	unsigned int	*value;
	int				size;
}					t_big_fraction;

typedef struct		s_exact_float
{
	char			type;
	char			sign;
	t_big_integer	integer;
	t_big_fraction	fraction;
	char			*integer_str;
	char			*fraction_str;
}					t_exact_float;

char				*integer_to_string(t_big_integer *n);
char				*fraction_to_string(t_big_fraction *n, int precision);
char				*fraction_to_string2(t_big_fraction *n, int precision);

t_exact_float		*double_to_exact_float(double d);
t_exact_float		*longdouble_to_exact_float(long double d);

#endif
