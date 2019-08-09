/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:47:29 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/20 16:22:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static long long	extract_data(t_printable *p)
{
	if (p->modifier == MOD_HH)
		return (*((char *)p->data));
	else if (p->modifier == MOD_H)
		return (*((short *)p->data));
	else if (p->modifier == MOD_L)
		return (*((long *)p->data));
	else if (p->modifier == MOD_LL)
		return (*((long long *)p->data));
	else
		return (*((int *)p->data));
}

char				*format_decimal(t_printable *p)
{
	long long	n;
	char		*str;
	char		*tmp;

	n = extract_data(p);
	if (n == 0 && p->precision == 0)
		str = ft_strdup("");
	else
		str = ft_itoa_base_u(ft_abs(n), "0123456789");
	if (!str)
		return (NULL);
	if (p->precision != -1)
	{
		p->flags &= ~ZEROPAD;
		if (!pad_left(&str, p->precision))
			return (NULL);
	}
	tmp = pad_number(p, num_prefix(p->flags, n < 0), str);
	free(str);
	return (tmp);
}
