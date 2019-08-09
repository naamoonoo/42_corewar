/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:51:04 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/13 15:52:36 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

ARGSIZE	size_char(char modifier)
{
	if (modifier == MOD_L)
		return (SIZE_CHAR);
	return (SIZE_CHAR);
}

ARGSIZE	size_int(char modifier)
{
	if (modifier == MOD_HH)
		return (SIZE_CHAR);
	else if (modifier == MOD_H)
		return (SIZE_SHORT);
	else if (modifier == MOD_L)
		return (SIZE_LONG);
	else if (modifier == MOD_LL)
		return (SIZE_LONGLONG);
	return (SIZE_INT);
}

ARGSIZE	size_double(char modifier)
{
	if (modifier == MOD_LD)
		return (SIZE_LONGDOUBLE);
	return (SIZE_DOUBLE);
}

ARGSIZE	size_ptr(char modifier)
{
	if (modifier == MOD_L)
		return (SIZE_PTR);
	return (SIZE_PTR);
}
