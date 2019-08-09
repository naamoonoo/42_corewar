/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unsigned_decimal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:43:19 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/30 13:31:06 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static unsigned long long	extract_data(t_printable *p)
{
	if (p->modifier == MOD_HH)
		return (*((unsigned char *)p->data));
	else if (p->modifier == MOD_H)
		return (*((unsigned short *)p->data));
	else if (p->modifier == MOD_L)
		return (*((unsigned long *)p->data));
	else if (p->modifier == MOD_LL)
		return (*((unsigned long long *)p->data));
	else
		return (*((unsigned int *)p->data));
}

char						*format_unsigned_decimal(t_printable *p)
{
	unsigned long long	n;
	char				*str;
	char				*tmp;

	n = extract_data(p);
	if (n == 0 && p->precision == 0)
		str = ft_strdup("");
	else
		str = ft_itoa_base_u(n, "0123456789");
	if (!str)
		return (NULL);
	if (p->precision != -1)
	{
		p->flags &= ~ZEROPAD;
		if (!pad_left(&str, p->precision))
			return (NULL);
	}
	tmp = pad_printable(p, "", str);
	free(str);
	return (tmp);
}
