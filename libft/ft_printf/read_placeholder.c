/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_placeholder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:42:18 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/05/20 16:28:51 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	pop_number(const char **format, BOOL arg_number)
{
	long		num;
	const char	*str;

	num = 0;
	str = *format;
	while (*str >= '0' && *str <= '9')
	{
		if (num < 2147483648)
		{
			num *= 10;
			num += *str - '0';
		}
		str++;
	}
	if (arg_number && (*str != '$'))
		return (0);
	if (arg_number)
		*format = str + 1;
	else
		*format = str;
	return (num > 2147483648 ? 0 : num);
}

static int	pop_flags(const char **format)
{
	int flags;

	flags = 0;
	while (1)
	{
		if (**format == '#')
			flags |= ALTFORM;
		else if ((**format == '0') && !(flags & RIGHTPAD))
			flags |= ZEROPAD;
		else if (**format == '-')
			flags = (flags | RIGHTPAD) & ~ZEROPAD;
		else if ((**format == ' ') && !(flags & SIGNFORCE))
			flags |= SIGNSPACE;
		else if (**format == '+')
			flags = (flags | SIGNFORCE) & ~SIGNSPACE;
		else if (**format == '\'')
			flags |= DELIMITERS;
		else if (**format != '0' && **format != ' ')
			return (flags);
		*format = *format + 1;
	}
}

static void	pop_width_and_precision(const char **format, t_printable *p)
{
	if (**format == '*')
	{
		*format = *format + 1;
		p->field_width_arg = pop_number(format, ARG);
	}
	else
		p->field_width = pop_number(format, NOT_ARG);
	if (**format == '.')
	{
		*format = *format + 1;
		if (**format == '*')
		{
			*format = *format + 1;
			p->precision_arg = pop_number(format, ARG);
		}
		else
			p->precision = pop_number(format, NOT_ARG);
	}
}

static char	pop_modifier(const char **format)
{
	if (**format == 'L')
	{
		*format = *format + 1;
		return (MOD_LD);
	}
	else if (**format == 'h')
	{
		*format = *format + 1;
		if (**format == 'h')
		{
			*format = *format + 1;
			return (MOD_HH);
		}
		return (MOD_H);
	}
	else if (**format != 'l')
		return (0);
	*format = *format + 1;
	if (**format == 'l')
	{
		*format = *format + 1;
		return (MOD_LL);
	}
	return (MOD_L);
}

int			read_placeholder(const char **format, t_list *printables)
{
	t_list		*elem;
	t_printable	*p;

	elem = new_printable();
	if (elem == NULL)
		return (-1);
	p = (t_printable *)elem->content;
	*format = *format + 1;
	p->data_arg = pop_number(format, ARG);
	p->flags = pop_flags(format);
	pop_width_and_precision(format, p);
	p->modifier = pop_modifier(format);
	p->type = **format;
	*format = *format + 1;
	ft_lstappend(printables, elem);
	return (0);
}
