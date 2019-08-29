/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unionstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 18:50:21 by aderby            #+#    #+#             */
/*   Updated: 2017/08/15 21:07:32 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	set_unsigned(t_printf **print1, int type, va_list *args)
{
	if (IS_OUX(type))
		UIM = (uintmax_t)va_arg(*args, unsigned int);
	else if (IS_UC(type))
		UIM = (uintmax_t)(unsigned char)va_arg(*args, unsigned int);
	else if (IS_USH(type))
		UIM = (uintmax_t)(unsigned short)va_arg(*args, unsigned int);
	else if (IS_UL(type))
		UIM = (uintmax_t)va_arg(*args, unsigned long);
	else if (IS_ULL(type))
		UIM = (uintmax_t)va_arg(*args, unsigned long long);
	else if (IS_UIM(type) || IS_P(type) || type == B_TYPE || type == BB_TYPE)
		UIM = (uintmax_t)va_arg(*args, uintmax_t);
	else if (IS_ST(type))
		UIM = (uintmax_t)va_arg(*args, size_t);
}

static void	set_signed(t_printf **print1, int type, va_list *args)
{
	if (IS_DI(type))
		IM = (intmax_t)va_arg(*args, int);
	if (IS_SC(type))
		IM = (intmax_t)(signed char)va_arg(*args, int);
	if (IS_SH(type))
		IM = (intmax_t)(short)va_arg(*args, int);
	else if (IS_L(type))
		IM = (intmax_t)va_arg(*args, long);
	else if (IS_LL(type))
		IM = (intmax_t)va_arg(*args, long long);
	else if (IS_IM(type))
		IM = (intmax_t)va_arg(*args, intmax_t);
}

static int	set_uniondata2(t_printf **print1, int type, va_list *args)
{
	if (type == WC_TYPE)
	{
		(*print1)->pid->fmt->wc = va_arg(*args, wchar_t);
		(*print1)->function = &pf_widechar;
	}
	else if (type == WS_TYPE)
	{
		if (!((*print1)->pid->fmt->ws = ft_wstrdup(va_arg(*args, wchar_t *))))
			return (0);
		(*print1)->function = &pf_widestr;
	}
	else if (type == PCNT_TYPE)
		(*print1)->function = &pf_percent;
	return (1);
}

int			set_uniondata(t_printf **print1, int type, va_list *args)
{
	if (type == C_TYPE)
	{
		(*print1)->pid->fmt->c = va_arg(*args, int);
		(*print1)->function = &pf_character;
	}
	else if (type == S_TYPE)
	{
		(*print1)->pid->fmt->s = ft_strdup(va_arg(*args, char *));
		(*print1)->function = &pf_string;
	}
	else if (IS_SIGNED(type) || IS_UNSIGNED(type))
	{
		IS_SIGNED(type) ? set_signed(print1, type, args)
			: set_unsigned(print1, type, args);
		(*print1)->function = IS_SIGNED(type) ? &pf_signedint : &pf_unsignedint;
	}
	else if (type == B_TYPE || type == BB_TYPE)
	{
		set_unsigned(print1, type, args);
		(*print1)->function = &pf_unsignedint;
	}
	else
		set_uniondata2(print1, type, args);
	return (1);
}
