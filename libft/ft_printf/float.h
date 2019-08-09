/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:53:54 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/18 18:08:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_H
# define FLOAT_H

typedef struct		s_float
{
	char			type;
	char			sign;
	int				exponent;
	unsigned long	significand;
}					t_float;

t_float				*parse_double(double d);
t_float				*parse_longdouble(long double d);
void				del_float(t_float **f);

#endif
