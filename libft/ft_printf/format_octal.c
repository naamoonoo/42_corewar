/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:11:55 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/20 19:12:34 by nwhitlow         ###   ########.fr       */
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

char						*format_octal(t_printable *p)
{
	unsigned long long	n;
	char				*str;
	char				*ostr;
	int					x;

	n = extract_data(p);
	x = (n == 0 && p->precision == 0 && !(p->flags & ALTFORM));
	str = x ? ft_strdup("") : ft_itoa_base_u(n, "01234567");
	if (!str)
		return (NULL);
	if (p->flags & ALTFORM && n)
	{
		ostr = ft_strsum("0", str);
		free(str);
		str = ostr;
	}
	if (p->precision != -1)
	{
		p->flags &= ~ZEROPAD;
		if (!pad_left(&str, p->precision))
			return (NULL);
	}
	ostr = pad_printable(p, num_prefix(p->flags, 0), str);
	free(str);
	return (ostr);
}
