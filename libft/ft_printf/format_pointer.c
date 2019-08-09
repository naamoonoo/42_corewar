/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:05:51 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/30 12:37:50 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*format_pointer(t_printable *p)
{
	p->flags |= ALTFORM;
	p->modifier = MOD_LL;
	p->type = 'x';
	if (!(*((void **)p->data)))
		return (pad_printable(p, "", "0x0"));
	return (format_hexadecimal(p));
}
